#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Player.hpp"
#include "Ball.hpp"
#include "Ai.hpp"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define SCREEN_MARGIN 200

class Game {
    public:
        Game();
        ~Game() = default;
        void run();
        sf::RectangleShape lineUp = sf::RectangleShape(sf::Vector2f(SCREEN_WIDTH - SCREEN_MARGIN, 4));
        sf::RectangleShape lineCenterY = sf::RectangleShape(sf::Vector2f(SCREEN_WIDTH - SCREEN_MARGIN, 2));
        sf::RectangleShape lineCenterX = sf::RectangleShape(sf::Vector2f(SCREEN_HEIGHT - SCREEN_MARGIN, 2));
        sf::RectangleShape lineDown = sf::RectangleShape(sf::Vector2f(SCREEN_WIDTH  - SCREEN_MARGIN, 4));
    private:
        void setup();
        void setupPlayer();
        void processEvents();
        void update(sf::Time deltaTime);
        void render();
        void handlePlayerInput();
    private:
        sf::Vector2i screenDimensions;
        sf::RenderWindow window;
        sf::RectangleShape table;
        Ball ball;
        Player player;
        Ai robot;
        sf::Font font;
        sf::Text text;

        const sf::Time TimePerFrame = sf::seconds(1.f/60.f);
        bool isPaused = false;

};