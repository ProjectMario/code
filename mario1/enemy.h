#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
class Enemy
{
public:
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
  float x, y;
  sf::FloatRect rect;
  sf::Sprite enemySprite;
  float frameCounter;
  bool isLife;

  Enemy(sf::Texture& image, int dx, int dy);
  void update(float time);
  void Collision();

};
#endif
