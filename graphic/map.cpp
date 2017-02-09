#include "map.hpp"
#include <string>
#include <sstream>

Map::Map(int h, int w, int wh, int ww) {
  this->height = h;
  this->width = w;
  this->window_height = wh;
  this->window_width = ww;
  if (!this->tile_texture.loadFromFile("./img/back.png", (sf::IntRect(0, 0, 128, 64))))
    std::cout << "Failed to load grass.jpg" << std::endl;
  /*if (!this->tile_bottom_left_texture.loadFromFile("./img/border_back.png", (sf::IntRect(0, 0, 64, 64))))
    std::cout << "Failed to load grass.jpg" << std::endl;*/
  if (!this->font.loadFromFile("Arcade.ttf"))
    std::cout << "Failed to load Arcade.ttf" << std::endl;

  if (!this->sprite_mage1_UP.loadFromFile("./img/mage_charset3.png"))
    std::cout << "Failed to load player.png" << std::endl;
  if (!this->sprite_mage1_DOWN.loadFromFile("./img/mage_charset2.png"))
    std::cout << "Failed to load playerdown" << std::endl;
  if (!this->sprite_mage1_LEFT.loadFromFile("./img/mage_charset4.png"))
    std::cout << "Failed to load playerleft" << std::endl;
  if (!this->sprite_mage1_RIGHT.loadFromFile("./img/mage_charset1.png"))
    std::cout << "Failed to load playerright" << std::endl;

  if (!this->sprite_mage2_UP.loadFromFile("./img/mage2_charset3.png"))
    std::cout << "Failed to load player.png" << std::endl;
  if (!this->sprite_mage2_DOWN.loadFromFile("./img/mage2_charset2.png"))
    std::cout << "Failed to load playerdown" << std::endl;
  if (!this->sprite_mage2_LEFT.loadFromFile("./img/mage2_charset4.png"))
    std::cout << "Failed to load playerleft" << std::endl;
  if (!this->sprite_mage2_RIGHT.loadFromFile("./img/mage2_charset1.png"))
    std::cout << "Failed to load playerright" << std::endl;

  if (!this->sprite_mage3_UP.loadFromFile("./img/mage3_charset3.png"))
    std::cout << "Failed to load player.png" << std::endl;
  if (!this->sprite_mage3_DOWN.loadFromFile("./img/mage3_charset2.png"))
    std::cout << "Failed to load playerdown" << std::endl;
  if (!this->sprite_mage3_LEFT.loadFromFile("./img/mage3_charset4.png"))
    std::cout << "Failed to load playerleft" << std::endl;
  if (!this->sprite_mage3_RIGHT.loadFromFile("./img/mage3_charset1.png"))
    std::cout << "Failed to load playerright" << std::endl;

  if (!this->linemate_texture.loadFromFile("./img/crystals.png", (sf::IntRect(0, 0, 54, 86))))
    std::cout << "Failed to load crystals" << std::endl;
  if (!this->deraumere_texture.loadFromFile("./img/crystals2.png", (sf::IntRect(0, 0, 54, 86))))
    std::cout << "Failed to load crystals2" << std::endl;
  if (!this->sibur_texture.loadFromFile("./img/crystals3.png", (sf::IntRect(0, 0, 54, 86))))
    std::cout << "Failed to load crystals3" << std::endl;
  if (!this->mendiane_texture.loadFromFile("./img/crystals4.png", (sf::IntRect(0, 0, 54, 86))))
    std::cout << "Failed to load crystals4" << std::endl;
  if (!this->phiras_texture.loadFromFile("./img/crystals5.png", (sf::IntRect(0, 0, 54, 86))))
    std::cout << "Failed to load crystals5" << std::endl;
  if (!this->thystame_texture.loadFromFile("./img/crystals6.png", (sf::IntRect(0, 0, 54, 86))))
    std::cout << "Failed to load crystals6" << std::endl;
  if (!this->food_texture.loadFromFile("./img/crystals7.png", (sf::IntRect(0, 0, 54, 86))))
    std::cout << "Failed to load crystals7" << std::endl;
}

Map::~Map() {

}

void Map::display(sf::RenderWindow &win) {
  sf::Text nbplayers;
  nbplayers.setFont(this->font);
  for (int x = 0; x < this->_map.size(); x++) {
    win.draw(this->_map[x].getShape());
    std::ostringstream ss;
    if (this->_map[x].getNbClient() > 0) {
      ss << this->_map[x].getNbClient();
      nbplayers.setString(ss.str());
      nbplayers.setPosition(this->_map[x].getShape().getPosition().x + 96,
                            this->_map[x].getShape().getPosition().y);
      nbplayers.setCharacterSize((this->window_width / this->width) / 2);
      win.draw(nbplayers);
    }
  }
  for (int m = 0; m < this->minerals.size(); m++) {
    win.draw(this->minerals[m].getShape());
  }
  /*for (int tm = 0; tm < this->minerals.size(); tm++) {
    if (this->height <= 13 && this->width <= 13)
      win.draw(this->minerals[tm].getText());
  }*/
  for (int p = 0; p < this->players.size(); p++) {
    win.draw(this->players[p].getShape());
  }
  win.display();
}

void Map::addTile(float x, float y, int nbclient) {
  int isoX = (x - y) * (128 / 2);
  int isoY = (x + y) * (64 / 2);
  Tile t(nbclient);
  t.getShape().setTexture(this->tile_texture);
  t.getShape().setPosition((this->window_width / 2) + isoX, isoY);
  this->_map.push_back(t);
}

void Map::mapping(t_server *server) {
  int ct = 0;
  for (int y = 0; y < this->height; y++) {
    for (int x = 0; x < this->width; x++) {
      this->addTile(x, y, server->map[y][x]->nbr_clients);
    }
  }
}

void Map::addPlayer(t_client *client) {
  int size = (this->window_height / this->height) / 4;
  int isoX = (client->x - client->y) * (128 / 2);
  int isoY = (client->x + client->y) * (64 / 2);
  Player p(client->squad->id);
  if (client->squad->id % 2 == 0) {
    switch (client->player_direction) {
      case UP : p.getShape().setTexture(this->sprite_mage1_UP); break;
      case DOWN : p.getShape().setTexture(this->sprite_mage1_DOWN); break;
      case LEFT : p.getShape().setTexture(this->sprite_mage1_LEFT); break;
      case RIGHT : p.getShape().setTexture(this->sprite_mage1_RIGHT); break;
      default : p.getShape().setTexture(this->sprite_mage1_UP); break;
    }
  }
  else if (client->squad->id % 3 == 0) {
    switch (client->player_direction) {
      case UP : p.getShape().setTexture(this->sprite_mage2_UP); break;
      case DOWN : p.getShape().setTexture(this->sprite_mage2_DOWN); break;
      case LEFT : p.getShape().setTexture(this->sprite_mage2_LEFT); break;
      case RIGHT : p.getShape().setTexture(this->sprite_mage2_RIGHT); break;
      default : p.getShape().setTexture(this->sprite_mage2_UP); break;
    }
  }
  else {
    switch (client->player_direction) {
      case UP : p.getShape().setTexture(this->sprite_mage3_UP); break;
      case DOWN : p.getShape().setTexture(this->sprite_mage3_DOWN); break;
      case LEFT : p.getShape().setTexture(this->sprite_mage3_LEFT); break;
      case RIGHT : p.getShape().setTexture(this->sprite_mage3_RIGHT); break;
      default : p.getShape().setTexture(this->sprite_mage3_UP); break;
    }
  }
  p.getShape().setPosition((this->window_width / 2) + isoX + 64, isoY - 32);
  this->players.push_back(p);
}

void Map::mapPlayers(t_server *server) {
  t_client *tmp;

  tmp = server->first;
  this->players.clear();
  while (tmp != NULL) {
    this->addPlayer(tmp);
    tmp = tmp->next;
  }
}

void Map::addMineral(ELEMENTS type, int nb, int x, int y) {
  int sizeY = (64 / 5) / 2;
  int sizeX = 64 / 5;
  int posX = (x - y) * (128 / 2);
  int posY = (x + y) * (64 / 2);
  Mineral m(type, nb);
  switch (type) {
    case LINEMATE : m.getShape().setTexture(this->linemate_texture); break;
    case DERAUMERE : m.getShape().setTexture(this->deraumere_texture); posX += sizeX; posY -= sizeY; break;
    case SIBUR : m.getShape().setTexture(this->sibur_texture); posX += sizeX * 2; posY -= sizeY * 2; break;
    case MENDIANE : m.getShape().setTexture(this->mendiane_texture); posX += sizeX; posY += sizeY; break;
    case PHIRAS : m.getShape().setTexture(this->phiras_texture); posX += sizeX * 2; break;
    case THYSTAME : m.getShape().setTexture(this->thystame_texture); posX += sizeX * 3; posY -= sizeY; break;
    case FOOD : m.getShape().setTexture(this->food_texture); posX += sizeX * 2; posY += sizeY * 3; break;
  }
  m.getShape().setPosition(posX + (this->window_width / 2), posY);
  m.getShape().scale(sf::Vector2f(0.35f, 0.35f));
  m.getText().setFont(this->font);
  std::ostringstream ss;
  ss << nb;
  m.getText().setString(ss.str());
  m.getText().setPosition(posX + (this->window_width / 2), posY);
  m.getText().setCharacterSize(sizeY * 2);
  this->minerals.push_back(m);
}

void Map::mapMinerals(t_server *server) {
  this->minerals.clear();
  for (int y = 0; y < this->height; y++) {
    for (int x = 0; x < this->width; x++) {
      if (server->map[y][x]->elem[LINEMATE] > 0)
        this->addMineral(LINEMATE, server->map[y][x]->elem[LINEMATE], x, y);
      if (server->map[y][x]->elem[DERAUMERE] > 0)
        this->addMineral(DERAUMERE, server->map[y][x]->elem[DERAUMERE], x, y);
      if (server->map[y][x]->elem[SIBUR] > 0)
        this->addMineral(SIBUR, server->map[y][x]->elem[SIBUR], x, y);
      if (server->map[y][x]->elem[MENDIANE] > 0)
        this->addMineral(MENDIANE, server->map[y][x]->elem[MENDIANE], x, y);
      if (server->map[y][x]->elem[PHIRAS] > 0)
        this->addMineral(PHIRAS, server->map[y][x]->elem[PHIRAS], x, y);
      if (server->map[y][x]->elem[THYSTAME] > 0)
        this->addMineral(THYSTAME, server->map[y][x]->elem[THYSTAME], x, y);
      if (server->map[y][x]->elem[FOOD] > 0)
        this->addMineral(FOOD, server->map[y][x]->elem[FOOD], x, y);
    }
  }
}
