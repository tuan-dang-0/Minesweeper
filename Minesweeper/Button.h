#pragma once
#include "TextureManager.h"
class Button{
    sf::Sprite buttonSprite;
    float xPos;
    float yPos;

public:
    Button();
    Button(float xPos, float yPos, const string& picName);
    void Draw(sf::RenderWindow& window);
    void SetPosition(float x, float y);
    sf::Rect<float> getGlobalBounds();
    float GetxPos();
    float GetyPos();
};