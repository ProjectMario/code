#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
class Player
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
  float coorX, coorY, frameCounter;
  int score;
  sf::FloatRect rect;
  bool onGround, direction = true, isLife = true;
  sf::Sprite animation;
  sf::Sprite rectMap;

  Player(sf::Texture &texture, sf::Texture &mapTexture);
  void update(float time);
  void setPlayerCoordForView(sf::View &view);
  void collision(int num);
};

#endif
