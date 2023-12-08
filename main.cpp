#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <time.h>
#include <iostream>
using namespace sf;

int N = 30, M = 20;				// dimensions for the window
int Ndash = 26, Mdash = 14;
int size = 16;					// the pixel size for the images 
int w = size * N;				// width
int h = size * M;				// hieght
int dir;						//for Directions
int num = 4;					// number of direction (left , right etc.)
float borderTime = 30;			//Time after which boundaries close

class Axis
{
public:
	int x;
	int y;
};

class Song 
{
public:
	Music theme_song;

	Song() 
	{
		theme_song.openFromFile("song/BGM_02.wav");
		theme_song.setVolume(30);
		theme_song.play();
		theme_song.setLoop(true);
	}
};
class Textures 
{
public:
	Texture t_platform, t_snake, t_fruit, t_border, tt_border;

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

	Sprites(Textures& textures) {
		s_platform.setTexture(textures.t_platform);
		s_snake.setTexture(textures.t_snake);
		s_fruit.setTexture(textures.t_fruit);
		s_border.setTexture(textures.t_border);
		ss_border.setTexture(textures.tt_border);
	}
};

class Snake : public Axis{};
class Fruit : public Axis{};

Snake s[100];
Fruit f;

void Tick()
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
		f.x = rand() % Ndash;
		f.y = rand() % Mdash;
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

	borderTime -= 1;
	std::cout << borderTime << std::endl;
}

int main()
{
	srand(time(0)); // initailizing random number generator

	RenderWindow window(VideoMode(w, h), "Snake Game!");
	Song theme_song;
	Textures textures;
	Sprites sprites(textures);

	
	f.x = 8;
	f.y = 8;

	Clock clock;
	float timer = 0, delay = 0.1;


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

		//drawing borders after colliders
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

		//snake collisions
		if (s[0].x == 0 || s[0].x == N - 1 || s[0].y == 0 || s[0].y == M - 1)
		{
			//DIE
			if (borderTime < 0)
			{
				
				exit(0);
			}

			
		}

		// drawing the Snake
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
