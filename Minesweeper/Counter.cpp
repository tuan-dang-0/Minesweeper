#include "Counter.h"

Counter::Counter(){
    texture.loadFromFile("images/digits.png");
    negative.setTexture(TextureManager::GetTexture("digits"));
    negative.setTextureRect(sf::IntRect(10 * 21, 0, 21, 32));
    for (sf::Sprite i : digits) {
        i.setTexture(TextureManager::GetTexture("digits"));
        i.setTextureRect(sf::IntRect(0, 0, 21, 32));
    }
    count = 0;
    isNegative = false;
}

Counter::Counter(float xPos, float yPos, int numMines){
    texture.loadFromFile("images/digits.png");
    negative.setTexture(TextureManager::GetTexture("digits"));
    negative.setTextureRect(sf::IntRect(10 * 21, 0, 21, 32));
    for (int i = 0; i < 3; i++) {
        digits[i] = sf::Sprite(TextureManager::GetTexture("digits"));
        digits[i].setTextureRect(sf::IntRect(0, 0, 21, 32));
    }
    SetPosition(xPos, yPos);
    count = numMines;
    isNegative = false;
}

void Counter::UpdateCounter(){

    int localCount = count;
    if(count < 0){
        isNegative = true;
        localCount *= (-1);
    }
    else
        isNegative = false;

    while(localCount > 999)
        localCount -= 1000;

    digits[0].setTextureRect(sf::IntRect(21 * (localCount / 10 / 10), 0, 21, 32));
    digits[1].setTextureRect(sf::IntRect(21 * (localCount / 10 % 10), 0, 21, 32));
    digits[2].setTextureRect(sf::IntRect(21 * (localCount % 10), 0, 21, 32));
}

void Counter::Draw(sf::RenderWindow& window){
    UpdateCounter();
    if(isNegative)
        window.draw(negative);
    for(int i = 0; i < 3; i++)
        window.draw(digits[i]);
}

void Counter::SetPosition(float xPos, float yPos){
    negative.setPosition(xPos, yPos);
    for(int i = 1; i < 4; i++)
        digits[i-1].setPosition(xPos + (21 * i), yPos);
}

void Counter::IncreaseCount(){
    count++;
}

void Counter::DecreaseCount(){
    count--;
}

void Counter::GameWon(){
    count = 0;
}
