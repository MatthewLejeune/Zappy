#ifndef _HPP_MAP_
#define _HPP_MAP_

#include "tile.hpp"
#include "mineral.hpp"

class Map {
  std::vector<Tile> _map;
  std::vector<Player> players;
  std::vector<Mineral> minerals;
  int height;
  int width;
  int window_height;
  int window_width;
  sf::Texture tile_texture;

  sf::Texture sprite_mage1_RIGHT;
  sf::Texture sprite_mage1_UP;
  sf::Texture sprite_mage1_LEFT;
  sf::Texture sprite_mage1_DOWN;

  sf::Texture sprite_mage2_RIGHT;
  sf::Texture sprite_mage2_UP;
  sf::Texture sprite_mage2_LEFT;
  sf::Texture sprite_mage2_DOWN;

  sf::Texture sprite_mage3_RIGHT;
  sf::Texture sprite_mage3_UP;
  sf::Texture sprite_mage3_LEFT;
  sf::Texture sprite_mage3_DOWN;

  sf::Texture linemate_texture;
  sf::Texture deraumere_texture;
  sf::Texture sibur_texture;
  sf::Texture mendiane_texture;
  sf::Texture phiras_texture;
  sf::Texture thystame_texture;
  sf::Texture food_texture;

  sf::Font font;

  public:
    Map(int, int, int, int);
    virtual ~Map();

    void display(sf::RenderWindow &);
    void mapping(t_server *);
    void addTile(float, float, int);
    void addPlayer(t_client *);
    void mapPlayers(t_server *);
    void mapMinerals(t_server *);
    void addMineral(ELEMENTS, int, int, int);
};

#endif
