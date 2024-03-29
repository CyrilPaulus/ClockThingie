
#include <iostream>
#include <vector>
#include "game.h"
#include "ball.h"
#include <gf/RenderWindow.h>
#include <gf/Window.h>
#include <gf/Sleep.h>

double crand(double start, double end) {
    std::cout << ((double) rand() / (RAND_MAX)) << std::endl;
    return start + (((double) rand() / (RAND_MAX))) * (end-start);
}

Game::Game(int width, int height) {
    _window = new gf::Window("Example", { width, height} );
    _renderer = new gf::RenderWindow(*_window);
}

void Game::Run() {
    gf::Clock clock;
    std::vector<Ball*> balls;

    unsigned int Seed = 10;
    
    for(int i = 0; i < 1000; i++) {
        Ball* ball = new Ball(gf::Vector2f(crand(0, 800), crand(0,600)), crand(4,10), 1);
        ball->attract_target = gf::Vector2f(crand(0, 800), crand(0,600));
        balls.push_back(ball);
    }
    

    while (_window->isOpen())
    {
        gf::Event event;
        while (_window->pollEvent(event))
        {
            if (event.type == gf::EventType::Closed) {
                _window->close();
                break;
            }

            if(event.type == gf::EventType::MouseButtonPressed) {
                for (Ball* b : balls) {                
                    b->attract = !b->attract;
                }
            }
            
        }

        gf::Time elapsed = clock.restart();
        float frametime = elapsed.asSeconds();
        Update(frametime);
        _renderer->clear();

        for (Ball* b : balls) {                
            b->Update(frametime, balls);
            b->Render(_renderer);
        }

        _window->display();
        gf::sleep(gf::milliseconds(10));
    }

    
}


void Game::Update(float frametime) {
    std::cout << "Fps " << 1/frametime << std::endl;
}