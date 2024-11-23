#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Ball.hpp"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define SCREEN_MARGIN 200
#define PLAYER_SIZE_X 35
#define PLAYER_SIZE_Y 56

class Ball;

class Ai {
    public:
        Ai(const sf::Vector2f& position);
        ~Ai() = default;
        void draw(sf::RenderTarget& window) const { window.draw(bat); }
        void update(const Ball& ball);
        sf::Vector2f getPosition() const { return bat.getPosition(); }
        float w = SCREEN_WIDTH - SCREEN_MARGIN;
        float h = SCREEN_HEIGHT - SCREEN_MARGIN -  2 * 10 + 5;
    private:
        //void setup();
        sf::RectangleShape bat;
        //sf::Vector2f velocity;
        //sf::Texture texture;
        sf::Clock clockAi;
        float deltaTimeAi = 0;
        float intPartSaved = 0;
};