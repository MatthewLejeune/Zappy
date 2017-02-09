#include "map.hpp"
#include "server.h"
#include <SFML/OpenGL.hpp>

extern pthread_mutex_t mu_graphic;

extern "C" void display(t_server *serv, void *arg) {
  sf::RenderWindow window;
  sf::View View(sf::FloatRect(-50, -200, 1200, 1200));
  sf::Event event;
  window.create(sf::VideoMode(1000, 1000), "Zappy");
  Map _map(serv->world_height, serv->world_width, 1000, 1000);
  window.setView(View);
  while (window.isOpen()) {
    t_server *server;
    pthread_mutex_lock (&mu_graphic);
    server = (t_server *)arg;
    pthread_mutex_unlock (&mu_graphic);
   _map.mapping(server);
   _map.mapPlayers(server);
   _map.mapMinerals(server);
   window.clear(sf::Color::Black);
   _map.display(window);
   while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
     window.close();
    }
  }
}
