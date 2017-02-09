#include "mineral.hpp"

Mineral::Mineral(ELEMENTS type, int nb) {
  sf::Sprite r;
  this->_mine = r;
  this->nb = nb;
}

Mineral::~Mineral() {

}

sf::Sprite &Mineral::getShape() {
  return this->_mine;
}

sf::Text &Mineral::getText() {
  return this->text;
}
