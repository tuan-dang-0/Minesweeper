#pragma once
#include "TextureManager.h"
class Smiley{
    sf::Sprite happyFace;
    sf::Sprite loseFace;
    sf::Sprite winFace;
    float xPos;
    float yPos;
    enum statuses {happy, lose, win};
    int status;

public:
    Smiley();
    Smiley(float xPos, float yPos);
    void Draw(sf::RenderWindow& window);
    void SetPosition(float x, float y);
    void SetLose();
    void SetWin();
    sf::Rect<float> getGlobalBounds();
    float GetxPos();
    float GetyPos();

};