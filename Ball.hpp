#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Ai.hpp"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define SCREEN_MARGIN 200
#define PLAYER_SIZE_X 35
#define PLAYER_SIZE_Y 56

enum class Side {Left, Right, Count};

class Ai;

class Ball {
    public:
        Ball(const sf::Vector2f& position);
        ~Ball() = default;
        void draw(sf::RenderTarget& window) const {window.draw(shape);}
        void update(const sf::Time deltaTime, sf::Text& text);
        void collision(Player& player);
        void collision(Ai& robot);
        std::map<Side, int> score = {{Side::Left, 0}, {Side::Right, 0}};
        sf::Vector2f getPosition() const { return position; }
        sf::Vector2f getVelocity() const { return velocity; }
    private:
        sf::Vector2f position;
        sf::Vector2f velocity = {150.f, 150.f};
        sf::CircleShape shape;
        static constexpr float speed = 150.f;
        void restart(sf::Text& text);
};