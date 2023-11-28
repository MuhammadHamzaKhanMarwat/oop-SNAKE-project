#include<iostream>
#include<SFML/Graphics.hpp>
using namespace sf;
int main()
{
	RenderWindow window(VideoMode(100, 100), "Snake");
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