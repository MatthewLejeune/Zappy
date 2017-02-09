#include "player.hpp"
#include <iostream>

Player::Player(int team) {
  sf::Sprite shape;
  this->teamnb = team;
  this->_player = shape;
}

Player::~Player() {

}

void Player::setTeam(int nb) {
  this->teamnb = nb;
}

sf::Sprite &Player::getShape() {
  return this->_player;
}
