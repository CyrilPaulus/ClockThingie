#pragma once
#include <gf/Event.h>
#include <gf/Font.h>
#include <gf/RenderWindow.h>
#include <gf/Sprite.h>
#include <gf/Text.h>
#include <gf/Window.h>

class Game {

    public:
        Game(int width, int height);
        void Run();

    private:
        gf::Window* _window;
        gf::RenderWindow* _renderer;

        void Update(float frametime);
        

};