#pragma once
#include <SFML/Graphics.hpp>


class Game {

    public:
        Game(int width, int height);
        void Run();

    private:
        sf::RenderWindow* _window;

        void Update(float frametime);
        

};