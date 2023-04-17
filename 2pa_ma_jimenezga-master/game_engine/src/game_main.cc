#include "game.h"

int main(int argc, char **argv) {
  Game g;

  g.init();
  g.mainLoop();
  g.end();

  return 0;
}