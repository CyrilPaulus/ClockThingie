#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Ball {

    public: 
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::Vector2f attract_target;
        float radius;
        float mass;
        bool attract = false;

        Ball(sf::Vector2f position, float radius, float mass);

        void Render(sf::RenderTarget* target);
        void Update(float frametime, const std::vector<Ball*>& balls);

    private: 
        sf::CircleShape shape;
        void Collide(Ball* ball);
        bool IsColliding(Ball* ball);
    
};