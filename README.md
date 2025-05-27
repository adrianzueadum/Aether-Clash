Aether Clash
Aether Clash is an exciting 2D top-down space shooter built using C++ and the SFML library. Pilot your spaceship through waves of enemy ships, shoot them down, and collect power-ups to boost your speed or damage. Survive as long as possible to achieve the highest score! This project is open-source and designed to showcase C++ game development skills. Your support through GitHub Sponsors helps keep this project growing with new features and improvements.
Features

Fast-paced top-down shooting gameplay.
Dynamic enemy waves with random spawning.
Power-ups for speed boosts and increased damage.
Score tracking to compete for the highest score.
Audio feedback for shooting actions.
Lightweight and extensible codebase.

Gameplay

Objective: Destroy enemy ships, collect power-ups, and survive as long as possible.
Controls:
Arrow Keys: Move the spaceship (left, right, up, down).
Spacebar: Fire bullets.


Scoring: Earn 10 points per enemy destroyed (20 points with damage power-up).
Power-ups: Green squares grant either a speed boost or double damage for a limited time.
Game Over: Colliding with an enemy ends the game.

Prerequisites
To build and run Aether Clash, you need:

A C++ compiler (e.g., g++).
SFML 2.5.1 or later installed and configured.
A font file (arial.ttf) for the score display.
A sound file (shoot.wav) for shooting sound effects.

Installation

Clone the Repository:
git clone https://github.com/yourusername/AetherClash.git
cd AetherClash


Install SFML:

Download SFML from sfml-dev.org.
Follow the installation instructions for your platform (Windows, macOS, or Linux).
Link SFML libraries (graphics, window, system, audio) in your project.


Add Resources:

Place arial.ttf (e.g., from Google Fonts) in the project directory.
Place shoot.wav (e.g., from Freesound) in the project directory.


Build the Project:

Example using g++:g++ -c main.cpp -I/path/to/sfml/include
g++ main.o -o AetherClash -L/path/to/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio




Run the Game:
./AetherClash



Project Structure

main.cpp: The main game source code.
arial.ttf: Font file for score display (not included, must be added).
shoot.wav: Sound file for shooting effect (not included, must be added).

Contributing
We welcome contributions to make Aether Clash even better! You can:

Report bugs or suggest features via GitHub Issues.
Submit pull requests with enhancements or fixes.
Share feedback to improve gameplay or code.

To contribute:

Fork the repository.
Create a new branch (git checkout -b feature/your-feature).
Commit your changes (git commit -m 'Add your feature').
Push to the branch (git push origin feature/your-feature).
Open a pull request.

Support the Project
Enjoy Aether Clash and want to see it grow? Support us through GitHub Sponsors! Your contributions help:

Add new features like boss enemies, leaderboards, or visual effects.
Maintain and optimize the codebase.
Keep Aether Clash free and open-source for the community.

Every donation helps us keep the project alive—thank you!
Future Plans

Add a main menu and game over screen with restart option.
Implement a high-score system with persistent storage.
Introduce boss enemies with unique patterns.
Add more power-up types (e.g., shield, rapid fire).
Include background music and additional sound effects.

License
This project is licensed under the MIT License. See the LICENSE file for details.
Acknowledgments

Built with SFML.
Inspired by classic arcade shooters.
Thanks to the open-source community for tools and resources.


Blast through the aether and thank you for playing Aether Clash!
