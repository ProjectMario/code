#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Player
{
private:
	int ground = 145;
public:
  float coorX, coorY;
  FloatRect rect;
  bool onGround, direction = true, life = true;
  Sprite animation;
  Sprite rectMap;

  float frameCounter;

  Vector2f GetPosition()
  {
    return animation.getPosition();
  }

  Player (Texture &texture, Texture &mapTexture)
  {
    animation.setTexture(texture);
    animation.setTextureRect(IntRect(0, 18, 16, 16));
    rect = FloatRect(0, 18, 16, 16);
    coorX = coorY = 0;
    frameCounter = 0;
    rectMap.setTexture(mapTexture);
  }
  void update(float time)
  {
    rect.left += coorX * time;

    if(!onGround)
    {
			cout << "coorX" << coorX << endl;
      coorY = coorY + 0.00075 * time;
			if(direction)
				animation.setTextureRect(IntRect(0*int(frameCounter), 0, 16, 16));
			if(!direction)
				animation.setTextureRect(IntRect(0*int(frameCounter) + 16, 0, -16, 16));

		}

    rect.top += coorY * time;

    if(rect.top > ground)
    {
      rect.top = ground;
      coorY = 0;
      onGround = true;
    }
    frameCounter += 0.02 * time;
    if(frameCounter > 4)
    {
      frameCounter -= 4;
    }
		if(coorX == 0 && onGround)
		{
			if(direction)
			{
				animation.setTextureRect(IntRect(0*int(frameCounter),18, 16, 16));
			}
			if(!direction)
			{
				animation.setTextureRect(IntRect(0*int(frameCounter) + 16 , 18, -16, 16));
			}
		}
    if(coorX > 0 && onGround)
    {
      animation.setTextureRect(IntRect(16*int(frameCounter),18, 16, 16));
    }
    if(coorX < 0 && onGround)
    {
      animation.setTextureRect(IntRect(16*int(frameCounter)+16,18, -16, 16));
    }
		if(rect.left < -4)
			rect.left ++;
		if(rect.left > 1588)
			rect.left --;
    animation.setPosition(rect.left, rect.top);

    coorX = 0;
  }
	void setPlayerCoordForView(View &view)
	{

		float x = rect.left;
		float y = rect.top;

	  if (x < 170)
	  {
	    x = 170;
	  }
	  if (x > 1430)
	  {
	    x = 1430;
	  }
	  if (y < 192)
	  {
	     y = 192;
	  }
		if (y > 96)
		{
			y = 96;
		}
	  view.setCenter(x, y);
	}
};

class Enemy
{
	Sprite enemyAnimation;
	bool life = true;
	int x,y;
	Enemy(Texture &texture, int dx, int dy)
	{
		x = dx;
		y = dy;
		enemyAnimation.setTexture(texture);
		enemyAnimation.setTextureRect(IntRect(0, 0, 16, 16))
	}
	void update(float time)
	{
		if(life)
		{
			enemyAnimation.setTextureRect(IntRect(0, 18, 16, 16))
		}
		else
		{
			enemyAnimation.setTextureRect(IntRect(0, 18, 16, 16))
		}
	}
};

int main()
{
		View view(Vector2f(170.0f, 96.0f), Vector2f(340.0f, 192.0f));
    RenderWindow window(VideoMode(340, 192), "Mario");

    Texture animationTexture;
    animationTexture.loadFromFile("Animation.png");

    Texture mapTexture;
    mapTexture.loadFromFile("Map.png");

    Player player(animationTexture, mapTexture);

		Texture animationOfEnemy;
		animationOfEnemy.loadFromFile("Enemy.png")
		Enemy enemy(animationOfEnemy);

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
					player.direction = false;
          player.setPlayerCoordForView(view);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
          player.coorX = 0.1;
					player.direction = true;
          player.setPlayerCoordForView(view);
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
          if(player.onGround)
          {
            player.coorY = -0.3;
            player.onGround = false;
          }
          player.setPlayerCoordForView(view);
        }
        player.update(time);
				window.setView(view);
        window.clear();
        window.draw(player.rectMap);
        window.draw(player.animation);
        window.display();

    }

    return 0;
}
