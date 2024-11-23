#include "Game.hpp"


Game::Game()
    : screenDimensions(SCREEN_WIDTH,SCREEN_HEIGHT)
    , window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pong")
    , ball(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2))
    , player(sf::Vector2f(100, 100))
    , robot(sf::Vector2f(SCREEN_WIDTH - SCREEN_MARGIN / 2, (SCREEN_HEIGHT - SCREEN_MARGIN) / 2))
{
    window.setFramerateLimit(60);
}

void Game::setup(){
    table = sf::RectangleShape(sf::Vector2f(SCREEN_WIDTH - SCREEN_MARGIN, SCREEN_HEIGHT - SCREEN_MARGIN));
    table.setFillColor(sf::Color::Green);
    table.setPosition(SCREEN_MARGIN / 2, SCREEN_MARGIN / 2);
    lineUp.setPosition(SCREEN_MARGIN / 2, SCREEN_HEIGHT / 2 - 10 - robot.h / 2);
    lineDown.setPosition(SCREEN_MARGIN / 2, SCREEN_HEIGHT  - SCREEN_MARGIN / 2);
    lineCenterY.setPosition(SCREEN_MARGIN / 2, SCREEN_HEIGHT / 2);
    lineCenterX.setPosition(SCREEN_WIDTH / 2, SCREEN_MARGIN / 2);
    lineCenterX.setRotation(90);
    if (!font.loadFromFile("resources/arial.ttf")) {
        std::cerr << "Error loading font\n";
        //return -1;
    }
    text.setFont(font); // font is a sf::Font
    text.setPosition(SCREEN_WIDTH / 2 - 22, SCREEN_MARGIN / 2 - 50);
    text.setString("0 : 0");
    text.setCharacterSize(24); // in pixels, not points!
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold); // | sf::Text::Underlined);
}

void Game::run(){
    setup();
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (window.isOpen()){
        processEvents();
        if (!isPaused) {
            timeSinceLastUpdate += clock.restart();
        } else {
            clock.restart();
        }
        while (timeSinceLastUpdate > TimePerFrame){
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            handlePlayerInput();
            update(TimePerFrame);
        }
        render();
    }
    std::cout << "Game is terminated" << std::endl;  
}

void Game::processEvents(){
    sf::Event event;
    while (window.pollEvent(event)){
        switch (event.type){
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
            isPaused = !isPaused; // Toggle the pause state
            if (isPaused)
                std::cout << "Game Paused\n";
            else
                std::cout << "Game Resumed\n";
        }
    }
}

void Game::handlePlayerInput(){
    sf::Vector2f direction(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        direction.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        direction.y += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        direction.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        direction.x += 1;
    player.setVelocity(direction);
}

void Game::update(sf::Time deltaTime){
    //ai.setPosition(ai.getPosition().x, ball.getPosition().y);
    ball.collision(robot);
    player.update(deltaTime);
    ball.update(deltaTime, text);
    ball.collision(player);
    robot.update(ball);
}

void Game::render(){
    window.clear(sf::Color::Black);
    window.draw(table);
    window.draw(lineUp);
    window.draw(lineCenterX);
    window.draw(lineCenterY);
    window.draw(lineDown);
    robot.draw(window);
    player.draw(window);
    ball.draw(window);
    window.draw(text);
    window.display();
}