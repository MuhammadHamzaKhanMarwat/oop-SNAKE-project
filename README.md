Snake Game using SFML
This project is an implementation of the classic Snake game using SFML, a multimedia library for C++. It offers a unique gameplay mechanic where the snake dynamically changes size upon conflicting directional inputs and restarts upon collision with borders.

Gameplay Features
Directional Conflicts: If the player inputs a conflicting direction while the snake is moving (e.g., left then right), the snake decreases in size.
Border Collision: The game restarts if the snake collides with the borders of the game window.
Endless Gameplay: The game doesn't have a finite endpoint, providing an endless playing experience.
Requirements
Ensure you have the following installed to run the game:

SFML library
C++ compiler
How to Run
Clone the repository to your local machine.
Install SFML and configure it properly.
Compile the source code using your preferred C++ compiler, linking the SFML libraries.
Run the compiled executable file.
Controls
Arrow Keys: Control the snake's direction.
WASD Keys: Alternative control scheme for direction.
ESC Key: Exit the game.
Game Logic Overview
The project consists of several classes:

Coordinates: Stores X and Y coordinates for game entities.
Song: Handles the game's theme song playback.
Textures: Manages the textures used in the game.
Sprites: Renders the textures onto the game window.
Snake: Inherits from Coordinates, representing the snake entity.
Fruit: Inherits from Coordinates, representing the fruit the snake consumes.
The main() function initializes the game window and handles user input, updating the game state accordingly.

Running the Game
bash
Copy code
# Clone the repository
git clone <repository_url>

# Compile the code (example using g++)
g++ -o SnakeGame main.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Run the executable
./SnakeGame
Feel free to modify and enhance the game logic or add features as needed!
