#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
class Player
{
private:
  bool onGround, direction, isLife;
  int score;
  float coorX, coorY, frameCounter;
public:
  static sf::String TileMap[12];
  static sf::String TileMap2[12];
  sf::FloatRect rect;
  sf::Sprite animation;
  sf::Sprite rectMap;

  Player(sf::Texture &texture, sf::Texture &mapTexture);
  bool getOnGround();
  bool getIsLife();
  float getX();
  float getY();
  int getScore();
  void setCoorX(float number);
  void setCoorY(float number);
  void increaseScore();
  void increaseScoreMore(int number);
  void changeOnGround(int number);
  void changeDirection(int number);
  void changeIsLife(int number);
  void update(float time);
  void setPlayerCoordForView(sf::View &view);
  void collision(int num);
};

#endif
