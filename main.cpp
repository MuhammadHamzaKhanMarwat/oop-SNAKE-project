#include<iostream>
#include<SFML/Graphics.hpp>
using namespace sf;
//Dimentions
int l = 800; // lenght
int w = 600; // width
int main()
{
	//Textures
	Texture t_snake, t_platform;
	t_snake.loadFromFile("image/red.png");
	t_platform.loadFromFile("image/green.png");

	//Sprite
	Sprite s_snake, s_platform;
	RenderWindow window(VideoMode(l,w), "Snake");
	while (window.isOpen())
	{
		Event E;
		while(window.pollEvent(E))
		{
			if (E.type == Event::Closed)
			{
				window.close();
			}
		}
		window.clear();
		window.display();
	}
	return 0;
}