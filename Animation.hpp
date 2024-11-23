#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
public:
    Animation(int x, int y, int width, int height)
    {
        //if (!texture.loadFromFile("resources/player-num.png", sf::IntRect(0, 0, 64 * 9, 64 * 4))){
        if (!texture.loadFromFile("resources/player.png", sf::IntRect(0, 0, 64 * 9, 64 * 4))){
            std::cerr << "Failed to load player texture!" << std::endl;
        }
        for (int i = 0; i < numFrames; i++)
        {
            //frames[i] = sf::IntRect(x + i * width, y, x + (i + 1) * width, y + height);
            frames[i] = sf::IntRect(x + i * width, y, width, height);
            //frames[i] = {x + i * width, y, width, height};
            //std::cout << "frames[" << i << "]=" << frames[i].left << ", " << frames[i].top << ", " << frames[i].width << ", " << frames[i].height << std::endl;
        }
    }
    void applyToSprite(sf::Sprite& sprite)
    {
        sprite.setTexture(texture);
        sprite.setTextureRect(frames[currentFrame]);
        //std::cout << "currentFrame=" << currentFrame << std::endl;
    }
    void update(float dt)
    {
        currentTime += dt;
        while (currentTime >= frameDuration)
        {
            currentTime -= frameDuration;
            advance();
        }
    }
private:
    void advance()
    {
        currentFrame++;
        if (currentFrame >= numFrames)
            currentFrame = 0;
        //std::cout << "currentFrame=" << currentFrame << std::endl;
    }
private:
    static constexpr int  numFrames = 9;
    static constexpr float  frameDuration = 0.1f;
    float currentTime = 0.0f;
    int currentFrame = 0;
    sf::Texture texture;
    sf::IntRect frames[numFrames];
};
