#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.hpp"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define SCREEN_MARGIN 200
#define PLAYER_SIZE_X 35
#define PLAYER_SIZE_Y 56

class Player {
    private:
        enum class Direction { Up, Down, Left, Right, Count};
    public:
        Player(const sf::Vector2f& position);
        ~Player() = default;
        void draw(sf::RenderTarget& window) const { 
            //window.draw(bat);
            window.draw(sprite);
        }
        void setVelocity(sf::Vector2f direction);
        sf::Vector2f getPosition() const { return position; }
        void update(const sf::Time deltaTime);
        sf::Vector2f movement = {0.f, 0.f};
        static constexpr float speed = 200.f;
    private:
        void setup();
        sf::RectangleShape bat;
        sf::Sprite sprite;
        sf::Vector2f position;
        sf::Texture texture;
        sf::Vector2f velocity;
        Animation animations[static_cast<int>(Direction::Count)] = {
            Animation(0, 64 * 0, 64, 64),  // Up
            Animation(0, 64 * 2, 64, 64),  // Down
            Animation(0, 64 * 1, 64, 64),  // Left
            Animation(0, 64 * 3, 64, 50)   // Right
        };
        Direction currentDirection = Direction::Count;
};