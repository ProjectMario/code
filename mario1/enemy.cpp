#include <SFML/Graphics.hpp>
#include "enemy.h"

using namespace std;
using namespace sf;

Enemy::Enemy(Texture& image, int dx, int dy)
{
  enemySprite.setTexture(image);
  rect = FloatRect(dx, dy, 15, 15);
  x = 0.05;
  frameCounter = 0;
  isLife = true;
}

void Enemy::update(float time)
{
  rect.left += x * time;
  Collision();
  frameCounter += time * 0.005;
  if(frameCounter > 2)
    frameCounter -= 2;
  if(x > 0)
		enemySprite.setTextureRect(IntRect(16*int(frameCounter) + 16, 0, -16, 16));
	else
		enemySprite.setTextureRect(IntRect(16*int(frameCounter), 0, 16, 16));
  if(!isLife)
		enemySprite.setTextureRect(IntRect(0, 17, 16, 16));

  enemySprite.setPosition(rect.left, rect.top);
}

void Enemy::Collision()
{
  for(int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
    for(int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
  	{
      if((TileMap[i][j] == 'G') || (TileMap[i][j] == '1') || (TileMap[i][j] == '2') || (TileMap[i][j] == '3') || (TileMap[i][j] == '4') || (TileMap[i][j] == 'L'))
  		{
        if(x > 0)
  			{
  				rect.left = j*16 - rect.width;
  				x *= -1;
  			}
        else if(x < 0)
  			{
  				rect.left = j*16 + 16;
  			 	x *= -1;
  			}
      }
    }
}
