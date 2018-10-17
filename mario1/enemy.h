#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
class Enemy
{
private:
  float frameCounter;
  bool isLife;
  float x, y;
public:
  sf::FloatRect rect;
  sf::Sprite enemySprite;

  Enemy(sf::Texture& image, int dx, int dy);
  void setX(float number);
  bool getIsLife();
  void changeIsLife(int number);
  void update(float time);
  void Collision();

};
#endif
