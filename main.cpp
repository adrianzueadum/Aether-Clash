#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <random>
#include <ctime>
#include <sstream>
#include <iostream>

// Window settings
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Player settings
const float PLAYER_SIZE = 30.0f;
const float PLAYER_SPEED = 300.0f;
const float BULLET_SPEED = 500.0f;
const float FIRE_RATE = 0.2f;

// Enemy settings
const float ENEMY_SIZE = 25.0f;
const float ENEMY_SPEED = 100.0f;
const float SPAWN_INTERVAL = 2.0f;

// Power-up settings
const float POWERUP_SIZE = 20.0f;
const float POWERUP_SPAWN_CHANCE = 0.1f;

class AetherClash {
private:
    sf::RenderWindow window;
    sf::RectangleShape player;
    std::vector<sf::RectangleShape> bullets;
    std::vector<sf::RectangleShape> enemies;
    std::vector<sf::RectangleShape> powerups;
    sf::Vector2f playerVelocity;
    float fireTimer;
    float spawnTimer;
    int score;
    sf::Font font;
    sf::Text scoreText;
    sf::Sound shootSound;
    sf::SoundBuffer shootBuffer;
    float speedBoost;
    float damageMultiplier;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<float> distX;
    std::uniform_real_distribution<float> distY;
    std::uniform_real_distribution<float> chance;

public:
    AetherClash() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Aether Clash"),
                    gen(rd()), distX(0.0f, WINDOW_WIDTH), distY(0.0f, WINDOW_HEIGHT / 2), chance(0.0f, 1.0f) {
        window.setFramerateLimit(60);

        // Initialize player
        player.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
        player.setFillColor(sf::Color::Cyan);
        player.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - PLAYER_SIZE * 2);
        playerVelocity = sf::Vector2f(0.0f, 0.0f);
        fireTimer = 0.0f;
        speedBoost = 1.0f;
        damageMultiplier = 1.0f;

        // Initialize score
        score = 0;
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Error loading font\n";
        }
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10.0f, 10.0f);

        // Initialize sound
        if (!shootBuffer.loadFromFile("shoot.wav")) {
            std::cerr << "Error loading shoot sound\n";
        }
        shootSound.setBuffer(shootBuffer);

        spawnTimer = 0.0f;
    }

    void handleInput() {
        playerVelocity = sf::Vector2f(0.0f, 0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) playerVelocity.x -= PLAYER_SPEED * speedBoost;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) playerVelocity.x += PLAYER_SPEED * speedBoost;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) playerVelocity.y -= PLAYER_SPEED * speedBoost;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) playerVelocity.y += PLAYER_SPEED * speedBoost;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && fireTimer <= 0.0f) {
            sf::RectangleShape bullet(sf::Vector2f(5.0f, 10.0f));
            bullet.setFillColor(sf::Color::Yellow);
            bullet.setPosition(player.getPosition().x + PLAYER_SIZE / 2 - 2.5f, player.getPosition().y);
            bullets.push_back(bullet);
            fireTimer = FIRE_RATE;
            shootSound.play();
        }
    }

    void update(float dt) {
        // Update player
        player.move(playerVelocity * dt);
        if (player.getPosition().x < 0) player.setPosition(0, player.getPosition().y);
        if (player.getPosition().x > WINDOW_WIDTH - PLAYER_SIZE) player.setPosition(WINDOW_WIDTH - PLAYER_SIZE, player.getPosition().y);
        if (player.getPosition().y < 0) player.setPosition(player.getPosition().x, 0);
        if (player.getPosition().y > WINDOW_HEIGHT - PLAYER_SIZE) player.setPosition(player.getPosition().x, WINDOW_HEIGHT - PLAYER_SIZE);

        // Update bullets
        for (auto it = bullets.begin(); it != bullets.end();) {
            it->move(0.0f, -BULLET_SPEED * dt);
            if (it->getPosition().y < 0) {
                it = bullets.erase(it);
            } else {
                ++it;
            }
        }

        // Spawn enemies
        spawnTimer += dt;
        if (spawnTimer >= SPAWN_INTERVAL) {
            sf::RectangleShape enemy(sf::Vector2f(ENEMY_SIZE, ENEMY_SIZE));
            enemy.setFillColor(sf::Color::Red);
            enemy.setPosition(distX(gen), 0.0f);
            enemies.push_back(enemy);
            if (chance(gen) < POWERUP_SPAWN_CHANCE) {
                sf::RectangleShape powerup(sf::Vector2f(POWERUP_SIZE, POWERUP_SIZE));
                powerup.setFillColor(sf::Color::Green);
                powerup.setPosition(distX(gen), distY(gen));
                powerups.push_back(powerup);
            }
            spawnTimer = 0.0f;
        }

        // Update enemies
        for (auto it = enemies.begin(); it != enemies.end();) {
            it->move(0.0f, ENEMY_SPEED * dt);
            if (it->getPosition().y > WINDOW_HEIGHT) {
                it = enemies.erase(it);
            } else {
                ++it;
            }
        }

        // Update power-ups
        for (auto it = powerups.begin(); it != powerups.end();) {
            if (player.getGlobalBounds().intersects(it->getGlobalBounds())) {
                if (chance(gen) < 0.5f) {
                    speedBoost = 1.5f;
                } else {
                    damageMultiplier = 2.0f;
                }
                it = powerups.erase(it);
            } else {
                ++it;
            }
        }

        // Check bullet-enemy collisions
        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
            bool bulletRemoved = false;
            for (auto enemyIt = enemies.begin(); enemyIt != enemies.end() && !bulletRemoved;) {
                if (bulletIt->getGlobalBounds().intersects(enemyIt->getGlobalBounds())) {
                    bulletIt = bullets.erase(bulletIt);
                    enemyIt = enemies.erase(enemyIt);
                    score += static_cast<int>(10 * damageMultiplier);
                    bulletRemoved = true;
                } else {
                    ++enemyIt;
                }
            }
            if (!bulletRemoved) ++bulletIt;
        }

        // Check player-enemy collisions
        for (const auto& enemy : enemies) {
            if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
                window.close(); // Game over
            }
        }

        // Update timers
        fireTimer -= dt;
        if (speedBoost > 1.0f) speedBoost -= dt * 0.1f;
        if (damageMultiplier > 1.0f) damageMultiplier -= dt * 0.1f;
        if (speedBoost < 1.0f) speedBoost = 1.0f;
        if (damageMultiplier < 1.0f) damageMultiplier = 1.0f;

        // Update score text
        std::stringstream ss;
        ss << "Score: " << score;
        scoreText.setString(ss.str());
    }

    void render() {
        window.clear(sf::Color::Black);
        window.draw(player);
        for (const auto& bullet : bullets) window.draw(bullet);
        for (const auto& enemy : enemies) window.draw(enemy);
        for (const auto& powerup : powerups) window.draw(powerup);
        window.draw(scoreText);
        window.display();
    }

    void run() {
        sf::Clock clock;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            float dt = clock.restart().asSeconds();
            handleInput();
            update(dt);
            render();
        }
    }
};

int main() {
    AetherClash game;
    game.run();
    return 0;
}
