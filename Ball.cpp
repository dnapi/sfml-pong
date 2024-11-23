#include "Ball.hpp"

Ball::Ball(const sf::Vector2f& position)
    : position(position)
{
    shape = sf::CircleShape(10);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);
}

void Ball::update(const sf::Time deltaTime, sf::Text& text){
    position += velocity * deltaTime.asSeconds();
    // left side of table
    if (position.x < 0){
        score[Side::Right]++;
        restart(text);
    }
    if (position.y < SCREEN_MARGIN / 2){
        position.y = SCREEN_MARGIN / 2;
        velocity.y *= -1;
    }
    // right side of table
    if (position.x > SCREEN_WIDTH - 2 * shape.getRadius()){
        score[Side::Left]++;
        restart(text);
    }
    if (position.y > SCREEN_HEIGHT - SCREEN_MARGIN / 2 - 2 * shape.getRadius()){
        position.y = SCREEN_HEIGHT - SCREEN_MARGIN / 2 - 2 * shape.getRadius();
        velocity.y *= -1;
    }
    shape.setPosition(position);
}

void Ball::collision(Player& player){
    // right side of player
    if (shape.getPosition().x > player.getPosition().x &&
        shape.getPosition().y > player.getPosition().y &&
        shape.getPosition().x < player.getPosition().x + PLAYER_SIZE_X &&
        shape.getPosition().y < player.getPosition().y + PLAYER_SIZE_Y){
        if (velocity.x < 0){
            velocity.x *= -1;
            shape.setPosition(player.getPosition().x, shape.getPosition().y);
        }
    }
}

void Ball::collision(Ai& robot){
    // left side of player
    if (shape.getPosition().x > SCREEN_WIDTH - SCREEN_MARGIN / 2 - 2 * shape.getRadius() &&
        shape.getPosition().y > robot.getPosition().y - 2 * shape.getRadius() &&
        shape.getPosition().y < robot.getPosition().y + PLAYER_SIZE_Y){
        if (velocity.x > 0){
            velocity.x *= -1;
            shape.setPosition(SCREEN_WIDTH - SCREEN_MARGIN / 2 - 2 * shape.getRadius(), shape.getPosition().y);
            //std::cout << "collision with robot" << std::endl;
        }
    }
    //std::cout << "ball vs ai x=" << shape.getPosition().x << " vs " << robot.getPosition().x << std::endl;
    //std::cout << "ball vs ai y=" << shape.getPosition().y << " vs " << robot.getPosition().y << std::endl;
}

void Ball::restart(sf::Text& text){
    text.setString(std::to_string(score[Side::Left]) + " : " 
                + std::to_string(score[Side::Right]));
    position = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    shape.setPosition(position);
    //velocity.x *= -1;
}