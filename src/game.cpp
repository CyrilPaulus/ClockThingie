
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include "game.h"
#include "ball.h"

double crand(double start, double end) {
    std::cout << ((double) rand() / (RAND_MAX)) << std::endl;
    return start + (((double) rand() / (RAND_MAX))) * (end-start);
}

Game::Game(int width, int height) {
    _window = new sf::RenderWindow(sf::VideoMode(width, height), "ClockThingie");
}

void Game::Run() {
    sf::Clock clock;
    std::vector<Ball*> balls;

    unsigned int Seed = 10;
    
    for(int i = 0; i < 1000; i++) {
        Ball* ball = new Ball(sf::Vector2f(crand(0, 800), crand(0,600)), crand(4,10), 1);
        ball->attract_target = sf::Vector2f(crand(0, 800), crand(0,600));
        balls.push_back(ball);
    }
    

    while (_window->isOpen())
    {
        sf::Event event;
        while (_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                _window->close();
                break;
            }

            if(event.type == sf::Event::MouseButtonPressed) {
                for (Ball* b : balls) {                
                    b->attract = !b->attract;
                }
            }
            
        }

        sf::Time elapsed = clock.restart();
        float frametime = elapsed.asSeconds();
        Update(frametime);
        _window->clear();

        for (Ball* b : balls) {                
            b->Update(frametime, balls);
            b->Render(_window);
        }

        _window->display();
        sf::sleep(sf::milliseconds(10));
    }

    
}


void Game::Update(float frametime) {
    std::cout << "Fps " << 1/frametime << std::endl;
}