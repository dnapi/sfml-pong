#include "Player.hpp"

Player::Player(const sf::Vector2f& position)
    : bat(sf::Vector2f(PLAYER_SIZE_X, PLAYER_SIZE_Y))
    , position(position)
    //animatedSprite(sf::seconds(0.2), true, false)
{
    setup();
    bat.setFillColor(sf::Color::Red);
    bat.setPosition(sf::Vector2f(100, 100));
}

void Player::setup(){
    if (!texture.loadFromFile("resources/player.png", sf::IntRect(0, 0, 64 * 4, 64 * 9))){
        std::cerr << "Failed to load player texture!" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
}

 void Player::setVelocity(sf::Vector2f direction){
    velocity = direction * speed;
    if (direction.x > 0){
        currentDirection = Direction::Right;
    } else if (direction.x < 0){
        currentDirection = Direction::Left;
    } else if (direction.y > 0){
        currentDirection = Direction::Down;
    } else if (direction.y < 0){
        currentDirection = Direction::Up;
    } else {
        currentDirection = Direction::Count;
    }
}

void Player::update(const sf::Time deltaTime){
    position += velocity * deltaTime.asSeconds();
    if (position.x < 0){
        position.x = 0;
    }
    if (position.y < 0){
        position.y= 0;
    }
    if (position.x > SCREEN_WIDTH - PLAYER_SIZE_X){
        position.x = SCREEN_WIDTH - PLAYER_SIZE_X;
    }
    if (position.y > SCREEN_HEIGHT - PLAYER_SIZE_Y){
        position.y = SCREEN_HEIGHT - PLAYER_SIZE_Y;
    }
    bat.setPosition(position);
    if (currentDirection != Direction::Count){
        animations[static_cast<int>(currentDirection)].update(deltaTime.asSeconds());
        animations[static_cast<int>(currentDirection)].applyToSprite(sprite);
    }
    //animations[static_cast<int>(currentDirection)].update(deltaTime.asSeconds());
    //animations[static_cast<int>(currentDirection)].applyToSprite(sprite);
    sprite.setPosition(position);
}