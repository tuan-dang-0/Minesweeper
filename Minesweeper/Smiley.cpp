#include "Smiley.h"

Smiley::Smiley() = default;

Smiley::Smiley(float xPos, float yPos){
    happyFace.setTexture(TextureManager::GetTexture("face_happy"));
    loseFace.setTexture(TextureManager::GetTexture("face_lose"));
    winFace.setTexture(TextureManager::GetTexture("face_win"));
    SetPosition(xPos, yPos);
    status = happy;

    this->xPos = xPos;
    this->yPos = yPos;
}

void Smiley::Draw(sf::RenderWindow& window){
    if(status == happy)
        window.draw(happyFace);
    if(status == lose)
        window.draw(loseFace);
    if(status == win)
        window.draw(winFace);
}
void Smiley::SetPosition(float x, float y){
    happyFace.setPosition(x, y);
    loseFace.setPosition(x, y);
    winFace.setPosition(x, y);
    xPos = x;
    yPos = y;
}

void Smiley::SetLose(){
    status = lose;
}

void Smiley::SetWin(){
    status = win;
}

sf::Rect<float> Smiley::getGlobalBounds(){
    return happyFace.getGlobalBounds();
}

float Smiley::GetxPos(){
    return xPos;
}

float Smiley::GetyPos(){
    return yPos;
}