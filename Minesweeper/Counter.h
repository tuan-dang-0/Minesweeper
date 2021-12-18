#pragma once
#include "TextureManager.h"

class Counter{
    sf::Texture texture;
    sf::Sprite negative;
    sf::Sprite digits[3];
    int count;
    bool isNegative;

public:
    Counter();
    Counter(float xPos, float yPos, int numMines);
    void UpdateCounter();
    void Draw(sf::RenderWindow& window);
    void SetPosition(float xPos, float yPos);
    void IncreaseCount();
    void DecreaseCount();
    void GameWon();
};