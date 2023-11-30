#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <time.h>
using namespace sf;

int N = 30, M = 20; // dimentions for the window
int size = 16; // the pixel size for the images 
int w = size * N; // width
int h = size * M; // hieght

int dir;
int num = 4;

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
    for (int i = num; i > 0; --i)
    {
        s[i].x = s[i - 1].x; s[i].y = s[i - 1].y;
    }

    if (dir == 0) s[0].y += 1;
    if (dir == 1) s[0].x -= 1;
    if (dir == 2) s[0].x += 1;
    if (dir == 3) s[0].y -= 1;

    if ((s[0].x == f.x) && (s[0].y == f.y))
    {
        num++; f.x = rand() % N; f.y = rand() % M;
    }

    if (s[0].x > N) s[0].x = 0;  
    if (s[0].x < 0) s[0].x = N;
    if (s[0].y > M) s[0].y = 0;  
    if (s[0].y < 0) s[0].y = M;

    for (int i = 1; i < num; i++)
        if (s[0].x == s[i].x && s[0].y == s[i].y)  num = i;
}

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(w, h), "Snake Game!");

    Texture t_platform, t_snake,t_fruit ;
    t_platform.loadFromFile("image/green.png");
    t_snake.loadFromFile("image/red.png");
    t_fruit.loadFromFile("image/white.png");
    Sprite s_platform(t_platform);
    Sprite s_snake(t_snake);
    Sprite s_fruit(t_fruit);
    
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

        if (Keyboard::isKeyPressed(Keyboard::Left)) dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right)) dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 0;

        if (timer > delay) { timer = 0; Tick(); }

        ////// draw  ///////
        window.clear();

        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
            {
                s_platform.setPosition(i * size, j * size);  window.draw(s_platform);
            }

        for (int i = 0; i < num; i++)
        {
            s_snake.setPosition(s[i].x * size, s[i].y * size);  window.draw(s_snake);
        }

        s_fruit.setPosition(f.x * size, f.y * size);  window.draw(s_fruit);

        window.display();
    }

    return 0;
}
 