#include "Ai.hpp"

Ai::Ai(const sf::Vector2f& position)
    : bat(sf::Vector2f(PLAYER_SIZE_X, PLAYER_SIZE_Y))
{
    //setup();
    bat.setFillColor(sf::Color::Blue);
    bat.setPosition(position);
}

void Ai::update(const Ball& ball){
    deltaTimeAi += clockAi.restart().asSeconds();
    if (deltaTimeAi > 1){
        deltaTimeAi = 0;
        sf::Vector2f v0 = ball.getVelocity();
        if (v0.x < 0)
            return;
        v0 = sf::Vector2f(v0.x, -v0.y);
        sf::Vector2f r0 = 
            sf::Vector2f(ball.getPosition().x, - ball.getPosition().y) -  
            sf::Vector2f(SCREEN_WIDTH / 2, - SCREEN_HEIGHT / 2) -
            sf::Vector2f(0, 10);
        if (v0.x == 0)
            v0 = {0.001, v0.y};
        float predictionY = r0.y + (w / 2 - 20 - r0.x) * v0.y / v0.x;
        float hightFromBorders = std::fabs(predictionY) - h / 2;
        //std::cout << "hightFromBorders=" << hightFromBorders << std::endl;
        if (hightFromBorders > 0){
            int intPart = hightFromBorders / h;
            float fracPart = hightFromBorders - (float)(intPart * h);
            //float intPart0;
            //hightFromBorders % h
            //float fracPart = std::modf(hightFromBorders / h, &intPart);
            predictionY = (h/2 - fracPart)
                * std::copysign(1.0f, v0.y)
                * std::pow(-1, intPart % 2);
            // if (intPartSaved != intPart)
            //     std::cout << "intPart=" << intPart << ", fracPart=" << fracPart << std::endl;
            // intPartSaved = intPart;
        }
        bat.setPosition(SCREEN_WIDTH - SCREEN_MARGIN / 2, - predictionY - 10 + SCREEN_HEIGHT / 2 - PLAYER_SIZE_Y / 2);
        //ai.setPosition(SCREEN_WIDTH - SCREEN_MARGIN / 2, 0 + SCREEN_HEIGHT / 2);
    }  
}
