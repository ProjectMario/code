#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

int ground = 145;
int offsetx = 0;
int offsety = 0;

class Player
{
public:
  float coorX, coorY;
  FloatRect rect;
  FloatRect map;
  bool onGround;
  Sprite animation;
  Sprite rectMap;

  float frameCounter;
  Player (Texture &texture, Texture &mapTexture)
  {
    animation.setTexture(texture);
    animation.setTextureRect(IntRect(0, 18, 16, 16));
    rect = FloatRect(0, 18, 16, 16);
    coorX = coorY = 0;
    frameCounter = 0;
    rectMap.setTexture(mapTexture);
    rectMap.setTextureRect(IntRect(0, 0, 340, 192));
    map = FloatRect(0, 0, 340, 192);
  }
  void update(float time)
  {
    rect.left += coorX * time;

    if (!onGround)
    {
      coorY = coorY + 0.00075 * time;
    }
    rect.top += coorY * time;
    onGround = false;

    if (rect.top > ground)
    {
      rect.top = ground;
      coorY = 0;
      onGround = true;
    }
    frameCounter += 0.02 * time;
    if (frameCounter > 4)
    {
      frameCounter -= 4;
    }
    if (coorX > 0)
    {
      animation.setTextureRect(IntRect(16*int(frameCounter),18, 16, 16));
    }
    if (coorX < 0)
    {
      animation.setTextureRect(IntRect(16*int(frameCounter)+16,18, -16, 16));
    }

    animation.setPosition(rect.left, rect.top);

    coorX = 0;
  }
  void tileMap()
  {
    if (map.left - rect.left < 70)
    {
    
    }
    if (rect.left - map.left < 70)
    {

    }
  }
};



int main()
{
    RenderWindow window(VideoMode(340, 192), "SFML works!");

    Texture animationTexture;
    animationTexture.loadFromFile("Animation.png");



    Texture mapTexture;
    mapTexture.loadFromFile("Map.png");

    Player player(animationTexture, mapTexture);

    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
          player.coorX = -0.1;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
          player.coorX = 0.1;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
          if(player.onGround)
          {
            player.coorY = -0.3;
            player.onGround = false;
          }
        }
        player.update(time);
        offsetx = player.rect.left;
        offsety = player.rect.top;
        player.tileMap();
        window.clear();
        window.draw(player.rectMap);
        window.draw(player.animation);
        window.display();
    }

    return 0;
}
