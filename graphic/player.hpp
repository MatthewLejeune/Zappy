#ifndef _HPP_PLAYER_
#define _HPP_PLAYER_

#include <SFML/Graphics.hpp>

class Player {
  sf::Sprite _player;
  int teamnb;

  public:
    Player(int);
    virtual ~Player();

    void setTeam(int);
    sf::Sprite &getShape();
};

#endif
