#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "game.h"

int main()
{
    Game game = Game(800, 600);
    game.Run();
    return 0;
}