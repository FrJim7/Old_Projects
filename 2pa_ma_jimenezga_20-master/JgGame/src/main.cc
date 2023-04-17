/**
 * JgGame
 * Francisco Jimenez Garcia <jimenezga@esat-alumni.com>
 * 2019 - 2020
 */
#include "game.h"

int main(int argc, char **argv) {
  Game g;
  
  g.init();
  g.load();
  g.loop();
  g.end();

  return 0;
}
