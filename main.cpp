#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <time.h>
#include <iostream>
using namespace sf;

// VARIABLE DECLEARATION

int N = 30, M = 20;				// dimensions for the window
int Ndash = 26, Mdash = 14;		// taking different mesurements for fruit so that it dont print it on the border
int size = 16;					// the pixel size for the images 
int w = size * N;				// width
int h = size * M;				// hieght
int dir;						// for Directions
int num = 4;					// number of direction (left , right etc.)
float borderTime = 5;			// Time after which boundaries close	
int score = 0;

// stores the main coordinates for the game (X Axis and Y Axis)
class Coordinates
{
public:
	int x;
	int y;
};

//stores and sort the theme song for the game 
class Song 
{
public:
	Music theme_song;
	// plays the theme song on repeat as long as the game is running
	Song() 
	{
		theme_song.openFromFile("song/BGM_02.wav");
		theme_song.setVolume(30);
		theme_song.play();
		theme_song.setLoop(true);
	}
	void Play_misic()
	{
		theme_song.play();
		theme_song.setLoop(true);
	}
	void Stop_music()
	{
		theme_song.stop();
	}
};

// used the enviroments texture
class Textures 
{
public:
	Texture t_platform, t_snake, t_fruit, t_border, tt_border;
	//store the textures of the game
	Textures() {
		t_platform.loadFromFile("image/green.png");
		t_snake.loadFromFile("image/red.png");
		t_fruit.loadFromFile("image/white.png");
		t_border.loadFromFile("image/border.png");
		tt_border.loadFromFile("image/border2.png");
	}
};

class Sprites 
{
public:
	Sprite s_platform, s_snake, s_fruit, s_border, ss_border;
	//it takes the textures and spread it around the screen
	Sprites(Textures& textures) {
		s_platform.setTexture(textures.t_platform);
		s_snake.setTexture(textures.t_snake);
		s_fruit.setTexture(textures.t_fruit);
		s_border.setTexture(textures.t_border);
		ss_border.setTexture(textures.tt_border);
	}
};

class Snake : public Coordinates {};

class Fruit : public Coordinates {};

//DECLEARING OBJECTS

Snake s[100];
Fruit f;
Song theme_song;
Textures textures;
Sprites sprites(textures);

static void Tick()
{
	// for moving the snakes head
	for (int i = num; i > 0; --i)
	{
		s[i].x = s[i - 1].x; s[i].y = s[i - 1].y;
	}

	if (dir == 0) s[0].y += 1;
	if (dir == 1) s[0].x -= 1;
	if (dir == 2) s[0].x += 1;
	if (dir == 3) s[0].y -= 1;

	// randomly printing / changing the fruit's location.
	if ((s[0].x == f.x) && (s[0].y == f.y))
	{
		num++;
		f.x = 1 + rand() % (2-Ndash);
		f.y = 1 + rand() % (2-Mdash);
	}

	// for errors (if the snake touches it tail / if it directly goes to left or right the snake)
	if (s[0].x > N)
	{
		s[0].x = 0;
	}
	if (s[0].x < 0)
	{
		s[0].x = N;
	}
	if (s[0].y > M)
	{
		s[0].y = 0;
	}
	if (s[0].y < 0)
	{
		s[0].y = M;
	}

	for (int i = 1; i < num; i++)
		if (s[0].x == s[i].x && s[0].y == s[i].y)
		{
			num = i;
		}
	// time countdown starts
	borderTime -= 1;
	std::cout << borderTime << std::endl;
}



// Reset snake position to the center
static void ResetSnake() 
{
	num = 4;
	dir = 0;
	s[0].x = N / 2;
	s[0].y = M / 2;
	for (int i = 1; i < num; ++i) 
	{
		s[i].x = s[0].x - i;
		s[i].y = s[0].y;
	}
}



// this draws the menu

void DrawMenu(RenderWindow& window) 
{
	theme_song.Stop_music();
	Font font;
	Texture menu;
	Sprite m_menu;
	menu.loadFromFile("image/Snake.jpg");
	m_menu.setTexture(menu);
	font.loadFromFile("font/Jockable.ttf");

	Text title("Snake Game", font, 60);
	title.setFillColor(Color::Green);
	title.setOutlineThickness(2);
	title.setOutlineColor(Color::Black);
	title.setPosition(60, 40);

	Text play("Play", font, 15);
	play.setStyle(Text::Style::Bold);
	play.setFillColor(Color::Green);
	play.setOutlineThickness(3);
	play.setOutlineColor(Color::Black);
	play.setPosition(220, 140);

	Text exit("Exit", font, 15);
	exit.setStyle(Text::Style::Bold);
	exit.setFillColor(Color::Green);
	exit.setOutlineThickness(3);
	exit.setOutlineColor(Color::Black);
	exit.setPosition(220, 170);

	while (window.isOpen()) 
	{
		window.clear();

		Event e;
		while (window.pollEvent(e)) 
		{
			if (e.type == Event::Closed)
				window.close();

			if (e.type == Event::MouseButtonPressed) 
			{
				if (e.key.code == Mouse::Button::Left) 
				{
					if (play.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) 
					{
						
						theme_song.Play_misic();
						ResetSnake();
						score = 0;
						return;
					}
					else if (exit.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) 
					{
						window.close();
					}
				}
			}
		}

		window.draw(m_menu);
		window.draw(title);
		window.draw(play);
		window.draw(exit);
		window.display();
	}
}


int main()
{


	srand(time(0)); // initailizing random number generator

	RenderWindow window(VideoMode(w, h), "Snake Game!");
	
	f.x = 8;
	f.y = 8;
	DrawMenu(window);
	Clock clock;
	float timer = 0, delay = 0.1;
	bool game_over = false;


	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}


		// keyboard input for arrow keys. 
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			dir = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			dir = 2;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			dir = 3;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			dir = 0;
		}
		// keyboard input for WASD.
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			dir = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			dir = 2;
		}
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			dir = 3;
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			dir = 0;
		}
		// When press ESC Key the user can exit the game
		if (Keyboard::isKeyPressed(Keyboard::Escape)) 
		{
			window.close();
		}


		if (timer > delay)
		{
			timer = 0;
			Tick();
		}
		window.clear();


		// drawing the platform
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				sprites.s_platform.setPosition(i * size, j * size);
				window.draw(sprites.s_platform);
			}
		}


		//drawing borders before colliders
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (i == 0 || i == N - 1 || j == 0 || j == M - 1)
				{
					sprites.s_border.setPosition(i * size, j * size);
					window.draw(sprites.s_border);
				}

			}
		}


		//drawing borders after colliders(snake Spawns first in 00 position so with the help of this it can spawn first in the center)
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (i == 0 || i == N - 1 || j == 0 || j == M - 1)
				{
					sprites.s_border.setPosition(i * size, j * size);
					window.draw(sprites.s_border);
				}

			}
		}


		for (int i = 1; i < num; ++i) {
			if (s[0].x == s[i].x && s[0].y == s[i].y) {
				game_over = true;
				break;
			}
		}


		// Snake collisions with border
		if (s[0].x == 0 || s[0].x == N - 1 || s[0].y == 0 || s[0].y == M - 1) 
		{
			if (borderTime < 0) 
			{
				game_over = true;
			}
		}


		// Drawing and setting up the score system
		score = num - 4;
		Font font;
		font.loadFromFile("font/We Love Peace.ttf");
		Text scoreText("Score: " + std::to_string(score), font, 20);
		scoreText.setFillColor(Color::White);
		scoreText.setOutlineThickness(2);
		scoreText.setOutlineColor(Color::Black);
		scoreText.Bold;
		scoreText.setPosition(10, 300);
		window.draw(scoreText);

		if (game_over) 
		{
			ResetSnake();
			game_over = false;
		}
		
		// Drawing snake 
		for (int i = 0; i < num; i++)
		{
			sprites.s_snake.setPosition(s[i].x * size, s[i].y * size);
			window.draw(sprites.s_snake);
		}

		// drawing the fruit.
		sprites.s_fruit.setPosition(f.x * size , f.y * size);
		window.draw(sprites.s_fruit);
		window.display();
	}

	return 0;
}
