#pragma once
#include <gf/Shapes.h>
#include <gf/Vector.h>
#include <gf/RenderTarget.h>

class Ball {

    public: 
        gf::Vector2f position;
        gf::Vector2f velocity;
        gf::Vector2f attract_target;
        float radius;
        float mass;
        bool attract = false;

        Ball(gf::Vector2f position, float radius, float mass);

        void Render(gf::RenderTarget* target);
        void Update(float frametime, const std::vector<Ball*>& balls);

    private: 
        gf::CircleShape shape;
        void Collide(Ball* ball);
        bool IsColliding(Ball* ball);
    
};