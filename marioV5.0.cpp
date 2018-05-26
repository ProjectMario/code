#include <SFML/Graphics.hpp>
//#include <SFML/Graphics/Font.hpp>
//#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include <sstream>
using namespace sf;
using namespace std;

sf::String TileMap[12] =
{
	"                                                                                                    ",
	"                                                                                                    ",
	"                                                                                                    ",
	"                                                                                                    ",
  "                                                                                                    ",
	"           C                                                                                        ",
	"      C   BBB    C                              L  L            C            L                      ",
	"     BBB       BBBB                            LL  LL          BBBB         LL                      ",
  "                          12         12       LLL  LLL                     LLL                      ",
	"                          34         34      LLLL  LLLL                   LLLL                      ",
  "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG  GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
	"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG  GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
};
class Player
{
private:
	int ground = 145;
public:
  float coorX, coorY;
	int score;
  FloatRect rect;
  bool onGround, direction = true, isLife = true;
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
		collision(0);
    if(!onGround)
    {
      coorY = coorY + 0.00075 * time;
			if(direction)
				animation.setTextureRect(IntRect(0*int(frameCounter), 0, 16, 16));
			if(!direction)
				animation.setTextureRect(IntRect(0*int(frameCounter) + 16, 0, -16, 16));

		}

    rect.top += coorY * time;
		onGround = false;
		collision(1);
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
	void collision(int num)
  {
    for (int i = rect.top/16  ; i < (rect.top + rect.height)/16 ; i++)
    for (int j = rect.left/16 ; j < (rect.left + rect.width)/16 ; j++)
		{
      if ((TileMap[i][j]=='G') || (TileMap[i][j]=='1') ||
          (TileMap[i][j]=='2') || (TileMap[i][j]=='3') ||
          (TileMap[i][j]=='4') || (TileMap[i][j]=='L') ||
					(TileMap[i][j]=='B'))
		    {
	        if (coorY > 0 && num == 1)
					{
						rect.top  = i*16 - rect.height;
						coorY = 0;
						onGround = true;
					}
	        if (coorY < 0 && num == 1)
				  {
						rect.top  = i*16 + 16;
						coorY = 0;
				  }
	        if (coorX > 0 && num == 0)
				  {
						 rect.left = j*16 - rect.width;
				  }
	        if (coorX < 0 && num == 0)
				  {
						rect.left = j*16 + 16	;
				  }
        }
					if (TileMap[i][j] == 'C')
					{
						score++;
						TileMap[i][j] = ' ';
					}
    }
  }
};



int main()
{
		View view(Vector2f(170.0f, 96.0f), Vector2f(340.0f, 192.0f));
    RenderWindow window(VideoMode(340, 192), "Mario");

    Texture animationTexture;
    animationTexture.loadFromFile("MarioGraphics/Animation.png");

		Texture mapTexture;
    mapTexture.loadFromFile("MarioGraphics/MapBack.png");

		Image mapImage;
		mapImage.loadFromFile("MarioGraphics/SpriteList.png");
    Texture map;
    map.loadFromImage(mapImage);
		Sprite mapSprite;
		mapSprite.setTexture(map);

/*sf::Font font;
 if(!font.loadFromFile("Fonts/OpenSans.ttf"))
 {
	cout << "Error" << endl;
 }
 sf::Text text;
 text.setFont(font);
 text.setColor(Color::Red);
text.setStyle(sf::Text::Bold | sf::Text::Underlined);
*/
    Player player(animationTexture, mapTexture);

	//	Texture animationOfEnemy;
	//	animationOfEnemy.loadFromFile("Enemy.png");
	//	Enemy enemy(animationOfEnemy);


	//	Font font;
	//	font.loadFromFile("CyrilicOld.ttf");
	//	Text text;
	//  text.setFont(font);
	//	text.setCharacterSize(50);
	//	text.setColor(sf::Color(0x555555ff));
	//	text.setStyle(sf::Text::Bold);
		RectangleShape rectangle;
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
				if(player.isLife)
				{
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
			  }
				else
				{

				}
			//	if(player.animation.getPosition().x > 1450)
			//	{
			//		text.setString("ты пидор");
			//		text.setPosition(view.getCenter().x, view.getCenter().y);
			//		window.draw(text);
			//	}
        player.update(time);
				window.setView(view);
        window.clear();
				window.draw(player.rectMap);
				for(int i = 0 ; i < 12 ; i++)
			    for(int j = 0 ; j < 100 ; j++)
					{
			      if(TileMap[i][j] == 'G')
						{
							mapSprite.setTextureRect(IntRect(34, 0, 16, 16));
						}
						if(TileMap[i][j] == 'B')
						{
							mapSprite.setTextureRect(IntRect(0, 0, 16, 16));
						}
						if(TileMap[i][j] == '1')
						{
							mapSprite.setTextureRect(IntRect(0, 17, 16, 16));
						}
						if(TileMap[i][j] == '2')
						{
							mapSprite.setTextureRect(IntRect(17, 17, 16, 16));
						}
						if(TileMap[i][j] == '3')
						{
							mapSprite.setTextureRect(IntRect(34, 17, 16, 16));
						}
						if(TileMap[i][j] == '4')
						{
							mapSprite.setTextureRect(IntRect(51, 17, 16, 16));
						}
						if(TileMap[i][j] == 'L')
					 	{
							mapSprite.setTextureRect(IntRect(17, 0, 16, 16));
						}
						if(TileMap[i][j] == 'C')
					 	{
							mapSprite.setTextureRect(IntRect(51, 0, 8, 8));
						}
			      if(TileMap[i][j] == ' ')
						 continue;

			      mapSprite.setPosition(j*16, i*16);
			      window.draw(mapSprite);
			    }

        window.draw(player.animation);
				//text.setString("Очки: ");
				//text.setPosition(0, 0);
				//window.draw(text);
        window.display();

    }

    return 0;
}
