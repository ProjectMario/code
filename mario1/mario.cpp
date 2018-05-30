#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include "player.h"
#include "enemy.h"
using namespace sf;
using namespace std;


int main()
{
	vector <Enemy> Enemies;

	View view(Vector2f(170.0f, 96.0f), Vector2f(340.0f, 192.0f));
  RenderWindow window(VideoMode(340, 192), "Mario", sf::Style::Fullscreen);

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

	Font font;
	font.loadFromFile("OpenSans.ttf");
	Text dieText(" ", font, 50);
	dieText.setFillColor(sf::Color::Red);
	dieText.setString("YOU DIE");
	Text restart(" ", font, 8);
	restart.setFillColor(sf::Color::Red);
	restart.setString("press Esc to exit or Space to back to top");
	sf::Text text(" ", font, 8);
	text.setFillColor(sf::Color::Blue);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

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
			if(Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
			if(player.getIsLife())
			{
        if(Keyboard::isKeyPressed(Keyboard::Left))
        {
          player.setCoorX(-0.1);
					player.changeDirection(0);
          player.setPlayerCoordForView(view);
        }
        if(Keyboard::isKeyPressed(Keyboard::Right))
        {
          player.setCoorX(0.1);
					player.changeDirection(1);
          player.setPlayerCoordForView(view);
        }
        if(Keyboard::isKeyPressed(Keyboard::Up))
        {
          if(player.getOnGround())
          {
            player.setCoorY(-0.3);
            player.changeOnGround(0);
          }
          player.setPlayerCoordForView(view);
        }
		  }
			else
			{
				if(Keyboard::isKeyPressed(Keyboard::Space))
				{

					player.changeIsLife(1);
					player.rect = FloatRect(0, 140, 16, 16);
					player.animation.setPosition(player.rect.left, player.rect.top);
					for(unsigned int i = 0; i < Enemies.size(); i++)
					{
						if(Enemies.at(i).getIsLife())
							{
								Enemies.at(i).changeIsLife(1);
								Enemies.at(i).setX(0.05);
							}
					}
				}
			}
      player.update(time);
			for(unsigned int i = 0; i < Enemies.size(); i++)
				Enemies.at(i).update(time);
			for(unsigned int i = 0; i < Enemies.size(); i++)
			{
				if(player.rect.intersects(Enemies.at(i).rect))
				{
				 if(Enemies.at(i).getIsLife() == true)
				 {
					 if(player.getY() > 0)
					 {
						 player.setCoorY(-0.2);
						 Enemies.at(i).setX(0);
						 Enemies.at(i).changeIsLife(0);
						 player.increaseScoreMore(20);
					 }
					 else
					 	player.changeIsLife(0);
				 }
			  }
			}
			window.setView(view);
      window.clear();
			window.draw(player.rectMap);
			for(unsigned int i = 0; i < Enemies.size(); i++)
				window.draw(Enemies.at(i).enemySprite);
			for(int i = 0 ; i < 12 ; i++)
			{
		    for(int j = 0 ; j < 100 ; j++)
				{
		      if(Player::TileMap[i][j] == 'G')
						mapSprite.setTextureRect(IntRect(34, 0, 16, 16));
					if(Player::TileMap[i][j] == 'B')
						mapSprite.setTextureRect(IntRect(0, 0, 16, 16));
					if(Player::TileMap[i][j] == '1')
						mapSprite.setTextureRect(IntRect(0, 17, 16, 16));
					if(Player::TileMap[i][j] == '2')
						mapSprite.setTextureRect(IntRect(17, 17, 16, 16));
					if(Player::TileMap[i][j] == '3')
						mapSprite.setTextureRect(IntRect(34, 17, 16, 16));
					if(Player::TileMap[i][j] == '4')
						mapSprite.setTextureRect(IntRect(51, 17, 16, 16));
					if(Player::TileMap[i][j] == 'L')
						mapSprite.setTextureRect(IntRect(17, 0, 16, 16));
					if(Player::TileMap[i][j] == 'C')
						mapSprite.setTextureRect(IntRect(51, 0, 8, 8));
		      if(Player::TileMap[i][j] == ' ')
					 continue;
		      mapSprite.setPosition(j*16, i*16);
		      window.draw(mapSprite);
		    }
			}
      window.draw(player.animation);
			ostringstream playerScoreS;
			playerScoreS << player.getScore();
			text.setString("Scores: " + playerScoreS.str());
			text.setPosition(view.getCenter().x - 165, view.getCenter().y - 95);
			window.draw(text);
			if(!player.getIsLife())
			{
				dieText.setPosition(view.getCenter().x - 90, view.getCenter().y - 50);
				window.draw(dieText);
				restart.setPosition(view.getCenter().x - 75, view.getCenter().y - 95);
				window.draw(restart);
			}
      window.display();

  }
	Enemies.clear();
  return 0;
}
