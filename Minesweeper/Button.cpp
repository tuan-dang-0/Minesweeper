#include "Button.h"

Button::Button() = default;

Button::Button(float xPos, float yPos, const string& picName){
    buttonSprite.setTexture(TextureManager::GetTexture(picName));
    this->xPos = xPos;
    this->yPos = yPos;
    SetPosition(xPos, yPos);
}

void Button::Draw(sf::RenderWindow& window){
    window.draw(buttonSprite);
}

void Button::SetPosition(float x, float y){
    buttonSprite.setPosition(x, y);
    xPos = x;
    yPos = y;
}

sf::Rect<float> Button::getGlobalBounds(){
    return buttonSprite.getGlobalBounds();
}

float Button::GetxPos(){
    return xPos;
}

float Button::GetyPos(){
    return yPos;
}
