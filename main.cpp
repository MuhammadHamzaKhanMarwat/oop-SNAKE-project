#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <time.h>
using namespace sf;

int N = 30, M = 20; // dimentions for the window
int size = 16; // the pixel size for the images 

int w = size * N; // width
int h = size * M; // hieght

int dir; //for Directions
int num = 4; // number of direction (left , right etc.)

class Snake
{
public:
	int x, y;
};

Snake s[100];

class Fruit
{
public:
	int x, y;
};

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

	// randomly printing / chaging the fruit's location.
	if ((s[0].x == f.x) && (s[0].y == f.y))
	{
		num++;
		f.x = rand() % N;
		f.y = rand() % M;
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
}

int main()
{
	srand(time(0)); // initailizing random number generator

	RenderWindow window(VideoMode(w, h), "Snake Game!");

	//Song 
	Music theme_song;
	theme_song.openFromFile("song/BGM_02.wav");
	theme_song.setVolume(30);
	theme_song.play();
	theme_song.setLoop(true);

	//Textures.

	Texture t_platform, t_snake, t_fruit, t_border;
	t_platform.loadFromFile("image/green.png");
	t_snake.loadFromFile("image/red.png");
	t_fruit.loadFromFile("image/white.png");
	t_border.loadFromFile("image/border.png");

	//Sprites.

	Sprite s_platform(t_platform);
	Sprite s_snake(t_snake);
	Sprite s_fruit(t_fruit);
	Sprite s_border(t_border);

	f.x = 10;
	f.y = 10;

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
				s_platform.setPosition(i * size, j * size);
				window.draw(s_platform);
			}
		}
		//drawing borders
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (i == 0 || i == N - 1 || j == 0 || j == M - 1)
				{
					s_border.setPosition(i * size, j * size);
					window.draw(s_border);
				}

			}
		}
		// drawing the Snake
		for (int i = 0; i < num; i++)
		{
			s_snake.setPosition(s[i].x * size, s[i].y * size);
			window.draw(s_snake);
		}
		// drawing the fruit.
		s_fruit.setPosition(f.x * size, f.y * size);
		window.draw(s_fruit);

		window.display();
	}

	return 0;
}
