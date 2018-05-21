#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

static const float VIEW_HEIGHT = 340.0f;
static const float VIEW_WIDTH = 192.0f;


  View view(Vector2f(170.0f, 96.0f), Vector2f(VIEW_HEIGHT, VIEW_WIDTH));




int ground = 145;
int offsetx = 0;
int offsety = 0;

class Player
{
public:
  float coorX, coorY;
  FloatRect rect;
  bool onGround;
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
	void setPlayerCoordForView()
	{

		float x = rect.left;
		float y = rect.top;
	  //std::cout << x << " " << y << '\n';

	  if (x < 170)
	  {
	    x = 170;
	    cout << "coorXl" << endl;
	    std::cout << x << '\n';
	  }
	  if (x > 1430)
	  {
	    x = 1430;
	    cout << "coorXR" << endl;
	    std::cout << x << '\n';
	  }

	  if (y < 67)
	  {
	     y = 67;
	     cout << "coorYl" << endl;
	     std::cout << y << '\n';
	  }


	  view.setCenter(x, y);

	}
};


int main()
{
    RenderWindow window(VideoMode(340, 192), "Mario");

    //View view(Vector2f(0.0f, 0.0f), Vector2f(VIEW_HEIGHT, VIEW_WIDTH));

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
          player.setPlayerCoordForView();
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
          player.coorX = 0.1;
          player.setPlayerCoordForView();
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
          if(player.onGround)
          {
            player.coorY = -0.3;
            player.onGround = false;
          }
          player.setPlayerCoordForView();
        }
        player.update(time);
				window.setView(view);
      //  view.setCenter(player.GetPosition());

        window.clear();
        window.draw(player.rectMap);
        window.draw(player.animation);
        window.display();

    }

    return 0;
}
