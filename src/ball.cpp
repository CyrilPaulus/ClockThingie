#include "ball.h"
#include <math.h>
#include <iostream>

#define GRAVITY 9.81 * 20
#define WIDTH 800
#define HEIGHT 600
#define COLLISION_LOST 0.9
#define FRICTION 0.995f


inline float dot(const sf::Vector2f& lv, const sf::Vector2f& rv)
{
    return lv.x * rv.x + lv.y * rv.y;
}

inline float length(const sf::Vector2f& source)
{
    return std::sqrt(dot(source, source));
}

inline sf::Vector2f normalize(const sf::Vector2f& source) {
    return source / length(source);
}

Ball::Ball(sf::Vector2f position, float radius, float mass) {

    this->position = position;
    this->velocity = sf::Vector2f(0, 0);
    this->radius = radius;
    this->mass = mass;
    this->shape = sf::CircleShape(this->radius, 100);
    this->attract_target = sf::Vector2f(0, 0);
}

void Ball::Render(sf::RenderTarget* target) {
    shape.setPosition(position);
    target->draw(shape);
}

void Ball::Update(float frametime, const std::vector<Ball*>& balls) {
    this->velocity = this->velocity*FRICTION;
    //Apply gravity
    this->velocity += sf::Vector2f(0, GRAVITY * frametime);

    if(this->attract) {
        sf::Vector2f to_center = normalize(this->attract_target - position);
        this->velocity += to_center * frametime * 1000.0f;
    }

    this->position += this->velocity * frametime;

    // for (Ball* ball : balls) {
    //     if (ball != this && IsColliding(ball))
    //         Collide(ball);
    // }


    if (this->position.y + 2 * this->radius > HEIGHT) {
        this->position.y = HEIGHT - 2 * radius;
        this->velocity.y = -COLLISION_LOST * this->velocity.y;
    }

    if (this->position.y <= 0) {
        this->position.y = 0;
        this->velocity.y = -COLLISION_LOST * this->velocity.y;
    }

    if (this->position.x <= 0) {
        this->position.x = 0;
        this->velocity.x = -COLLISION_LOST * this->velocity.x;
    }

    if (this->position.x + 2 * this->radius > WIDTH) {
        this->position.x = WIDTH - 2 * this->radius;
        this->velocity.x = -COLLISION_LOST * this->velocity.x;
    }

   
    

    
}

bool Ball::IsColliding(Ball* other) {
    sf::Vector2f center = this->position + sf::Vector2f(this->radius, this->radius);
    sf::Vector2f other_center = other->position + sf::Vector2f(other->radius, other->radius);
    float radiusSum = this->radius + other->radius;

    return length(center - other_center) < radiusSum;
}

void Ball::Collide(Ball* other) {
    sf::Vector2f delta = this->position - other->position;
    float d = length(delta);
    sf::Vector2f mtd = delta * (this->radius + other->radius -d)/d;

    float im1 = 1 / this->mass;
    float im2 = 1 / other->mass;

    this->position = this->position + mtd * (im1 / (im1 + im2));
    other->position = other->position - mtd * (im2 / (im1 + im2));

    sf::Vector2f v = this->velocity - other->velocity;
    float vn = dot(v, normalize(mtd));

    if (vn > 0.0f)
        return;

    float i = COLLISION_LOST * vn / (im1 + im2);
    sf::Vector2f impulse = -normalize(mtd) * i;
    this->velocity += impulse * im1;
    other->velocity -= impulse * im2;
}