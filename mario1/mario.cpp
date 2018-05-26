#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "enemy.h"
using namespace sf;
using namespace std;


int main()
{
	vector <Enemy> Enemies;
	View view(Vector2f(170.0f, 96.0f), Vector2f(340.0f, 192.0f));
  RenderWindow window(VideoMode(340, 192), "Mario");

  Texture animationTexture;
  animationTexture.loadFromFile("image/Animation.png");

	Texture mapTexture;
  mapTexture.loadFromFile("image/MapBack.png");
	Player player(animationTexture, mapTexture);
	Image mapImage;
	mapImage.loadFromFile("image/SpriteList.png");
  Texture map;
  map.loadFromImage(mapImage);
	Sprite mapSprite;
	mapSprite.setTexture(map);

	Texture animationOfEnemy;
	animationOfEnemy.loadFromFile("image/Enemy.png");
	Enemies.push_back(Enemy(animationOfEnemy, 560, 145));
	Enemies.push_back(Enemy(animationOfEnemy, 1150, 145));
	Enemies.push_back(Enemy(animationOfEnemy, 1050, 145));
	Enemies.push_back(Enemy(animationOfEnemy, 660, 145));
  Clock clock;

  while (window.isOpen())
  {
      float time = clock.getElapsedTime().asMicroseconds();
      clock.restart();
      time = time / 800;

      Event event;
      while(window.pollEvent(event))
      {
          if(event.type == Event::Closed)
              window.close();
      }
			if(player.isLife)
			{
        if(Keyboard::isKeyPressed(Keyboard::Left))
        {
          player.coorX = -0.1;
					player.direction = false;
          player.setPlayerCoordForView(view);
        }
        if(Keyboard::isKeyPressed(Keyboard::Right))
        {
          player.coorX = 0.1;
					player.direction = true;
          player.setPlayerCoordForView(view);
        }
        if(Keyboard::isKeyPressed(Keyboard::Up))
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
      player.update(time);
			for(unsigned int i = 0; i < Enemies.size(); i++)
				Enemies.at(i).update(time);
			for(unsigned int i = 0; i < Enemies.size(); i++)
			{
				if(player.rect.intersects(Enemies.at(i).rect))
				{
				 if(Enemies.at(i).isLife == true)
				 {
					 if(player.coorY > 0)
					 {
						 player.coorY = -0.2;
						 Enemies.at(i).x = 0;
						 Enemies.at(i).isLife = false;
					 }
				 }
			  }
			}
			window.setView(view);
      window.clear();
			window.draw(player.rectMap);
			for(int i = 0 ; i < 12 ; i++)
			{
		    for(int j = 0 ; j < 100 ; j++)
				{
		      if(player.TileMap[i][j] == 'G')
					{
						mapSprite.setTextureRect(IntRect(34, 0, 16, 16));
					}
					if(player.TileMap[i][j] == 'B')
					{
						mapSprite.setTextureRect(IntRect(0, 0, 16, 16));
					}
					if(player.TileMap[i][j] == '1')
					{
						mapSprite.setTextureRect(IntRect(0, 17, 16, 16));
					}
					if(player.TileMap[i][j] == '2')
					{
						mapSprite.setTextureRect(IntRect(17, 17, 16, 16));
					}
					if(player.TileMap[i][j] == '3')
					{
						mapSprite.setTextureRect(IntRect(34, 17, 16, 16));
					}
					if(player.TileMap[i][j] == '4')
					{
						mapSprite.setTextureRect(IntRect(51, 17, 16, 16));
					}
					if(player.TileMap[i][j] == 'L')
				 	{
						mapSprite.setTextureRect(IntRect(17, 0, 16, 16));
					}
					if(player.TileMap[i][j] == 'C')
				 	{
						mapSprite.setTextureRect(IntRect(51, 0, 8, 8));
					}
		      if(player.TileMap[i][j] == ' ')
					 continue;

		      mapSprite.setPosition(j*16, i*16);
		      window.draw(mapSprite);
		    }
			}
			for(unsigned int i = 0; i < Enemies.size(); i++)
				window.draw(Enemies.at(i).enemySprite);
      window.draw(player.animation);
      window.display();

  }

  return 0;
}
