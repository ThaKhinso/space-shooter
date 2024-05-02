#include "Game.h"


int main() {
    std::shared_ptr<Game> game = std::make_shared<Game>();
    game->Run();
}