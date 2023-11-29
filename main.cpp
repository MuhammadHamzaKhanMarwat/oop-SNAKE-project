#include<iostream>
#include<SFML/Graphics.hpp>
using namespace sf;
//Dimentions
int N = 40, M = 20;
int size = 16;
int l = N*size; // lenght
int w = M*size; // width

int dir, num = 4;
class Snake
{
public:
	int x, y;
};
Snake s[100];

void tick()
{
	for (int i = num; i > num; i--)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}
	switch (dir)
	{
	case 0:
		s[0].y += 1;
	case 1:
		s[0].x -= 1;
	case 2:
		s[0].x += 1;
	case 3:
		s[0].y -= 1;
	
	default:
		//Empty
		break;
	}
}
int main()
{
	RenderWindow window(VideoMode(l, w), "Snake");

	//Textures
	Texture t_snake, t_platform;
	t_snake.loadFromFile("image/red.png");
	t_platform.loadFromFile("image/green.png");

	//Sprite
	Sprite s_snake(t_snake);
	Sprite s_platform(t_platform);

	Clock clock;
	float timer = 0, delay = 0.1;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds;
		timer += time;

		Event E;
		while(window.pollEvent(E))
		{
			if (E.type == Event::Closed)
			{
				window.close();
			}
		}
		if (timer>delay)
		{
			timer = 0;
			tick();
		}

		window.clear();

		//drawing the platform
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M ; j++)
			{
				s_platform.setPosition(i*size, j*size);
				window.draw(s_platform);
			}
		}
		window.display();
	}
	return 0;
}