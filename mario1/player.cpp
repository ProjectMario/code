#include <SFML/Graphics.hpp>
#include "player.h"

using namespace std;
using namespace sf;

sf::String Player::TileMap[12] =
{
  "                                                                                                    ",
  "                                                                                                    ",
  "                                                                                                    ",
  "                                                                                                    ",
  "                                                                                                    ",
  "           C                                                                 C                      ",
  "      C   BBB    C                              L  L            C            L                      ",
  "     BBB       BBBB                            LL  LL          BBBB         LL                      ",
  "                          12         12       LLL  LLL                     LLL                      ",
  "                          34         34      LLLL  LLLL                   LLLL                      ",
  "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG  GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
  "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG  GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
};

Player::Player(Texture &texture, Texture &mapTexture)
{
  animation.setTexture(texture);
  animation.setTextureRect(IntRect(0, 18, 16, 16));
  rect = FloatRect(0, 140, 16, 16);
  coorX = coorY = 0;
  frameCounter = 0;
  rectMap.setTexture(mapTexture);
  direction = true;
  isLife = true;
}
bool Player::getIsLife()
{
  return isLife;
}
bool Player::getOnGround()
{
  return onGround;
}
float Player::getX()
{
  return coorX;
}
float Player::getY()
{
  return coorY;
}
int Player::getScore()
{
  return score;
}
void Player::setCoorX(float number)
{
  coorX = number;
}
void Player::setCoorY(float number)
{
  coorY = number;
}
void Player::increaseScore()
{
  score++;
}
void Player::increaseScoreMore(int number)
{
  score += number;
}
void Player::changeOnGround(int number)
{
  if(number == 1)
    onGround = true;
  if(number == 0)
    onGround = false;
}
void Player::changeDirection(int number)
{
  if(number == 1)
    direction = true;
  if(number == 0)
    direction = false;
}
void Player::changeIsLife(int number)
{
  if(number == 1)
    isLife = true;
  if(number == 0)
    isLife = false;
}
void Player::update(float time)
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
  rect.top += getY() * time;
  changeOnGround(0);
  collision(1);
  frameCounter += 0.02 * time;
  if(frameCounter > 4)
    frameCounter -= 4;
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
    animation.setTextureRect(IntRect(16*int(frameCounter),18, 16, 16));
  if(coorX < 0 && onGround)
    animation.setTextureRect(IntRect(16*int(frameCounter) + 16,18, -16, 16));
  if(rect.left < -4)
    rect.left ++;
  if(rect.left > 1588)
    rect.left --;
  animation.setPosition(rect.left, rect.top);
  setCoorX(0);
}

void Player::setPlayerCoordForView(View &view)
{
  float x = rect.left;
  float y = rect.top;
  if(x < 170)
    x = 170;
  if(x > 1430)
    x = 1430;
  if(y < 192)
    y = 192;
  if(y > 96)
    y = 96;
  view.setCenter(x, y);
}

void Player::collision(int num)
{
  if(((rect.top + rect.height) / 16) >= 12)
  {
    isLife = false;
    onGround = true;
    return;
  }
  for(int i = rect.top / 16  ; i < (rect.top + rect.height) / 16 ; i++)
    for(int j = rect.left / 16 ; j < (rect.left + rect.width) / 16 ; j++)
    {
      if((TileMap[i][j] == 'G') || (TileMap[i][j] == '1') ||
          (TileMap[i][j] == '2') || (TileMap[i][j] == '3') ||
          (TileMap[i][j] == '4') || (TileMap[i][j] == 'L') ||
          (TileMap[i][j] == 'B'))
        {
          if(coorY > 0 && num == 1)
          {
            rect.top  = i*16 - rect.height;
            coorY = 0;
            changeOnGround(1);
          }
          if(coorY < 0 && num == 1)
          {
            rect.top  = i*16 + 16;
            coorY = 0;
          }
          if(coorX > 0 && num == 0)
            rect.left = j*16 - rect.width;
          if(coorX < 0 && num == 0)
            rect.left = j*16 + 16	;
        }
      if(TileMap[i][j] == 'C')
      {
        increaseScore();
        TileMap[i][j] = ' ';
      }
    }
}
