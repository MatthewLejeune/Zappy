#include "tile.hpp"

Tile::Tile(int nbclient) {
  sf::Sprite r;
  this->_tileset = r;
  this->nbclient = nbclient;
}

Tile::~Tile() { }

sf::Sprite &Tile::getShape() {
  return this->_tileset;
}

int Tile::getNbClient() {
  return this->nbclient;
}
