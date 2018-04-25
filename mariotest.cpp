#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

int ground = 170;

class Player
{
public:
  float coorX, coorY;
  FloatRect rect;
  bool onGround;
  Sprite animation;

  float frameCounter;
  Player (Texture &texture)
  {
    animation.setTexture(texture);
    animation.setTextureRect(IntRect(0, 18, 16, 16));
    rect = FloatRect(0, 18, 16, 16);
    coorX = coorY = 0;
    frameCounter = 0;
  }
  void update(float time)
  {
    rect.left += coorX * time;

    if (!onGround)
    {
      coorY = coorY + 0.001 * time;
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
};
int main()
{
    RenderWindow window(VideoMode(1600, 192), "SFML works!");

    Texture animationTexture;
    animationTexture.loadFromFile("Animation.png");

    Player player(animationTexture);

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
        window.clear();
        window.draw(player.animation);
        window.display();
    }

    return 0;
}
