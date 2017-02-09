#ifndef _HPP_TILE_
#define _HPP_TILE_

#include <iostream>
#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <map>
#include "server.h"

class Tile {
  sf::Sprite _tileset;
  int nbclient;

  public:
    Tile(int);
    virtual ~Tile();

    sf::Sprite &getShape();
    int getNbClient();
};

#endif
