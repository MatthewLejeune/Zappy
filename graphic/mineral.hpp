#ifndef _HPP_MINERAL_
#define _HPP_MINERAL_

#include "server.h"
#include <SFML/Graphics.hpp>

class Mineral {
  sf::Sprite _mine;
  ELEMENTS type;
  int nb;
  sf::Text text;

  public:
    Mineral(ELEMENTS, int);
    virtual ~Mineral();

    sf::Sprite &getShape();
    sf::Text &getText();
};

#endif
