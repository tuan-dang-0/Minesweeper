#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"


class Tile{
    sf::Sprite hiddenTile;
    sf::Sprite revealedTile;
    sf::Sprite mine;
    sf::Sprite flag;
    sf::Sprite num;
    bool isRevealed;
    bool isMine;
    bool isFlagged;
    int numAdjMines;

public:
    std::vector<Tile*> adjacent;
    Tile();
    void Draw(sf::RenderWindow& window);
    void DrawMine(sf::RenderWindow& window);
    void Reveal();
    void SetPosition(float x, float y);
    bool setMine();
    bool isAMine() const;
    sf::Rect<float> getGlobalBounds();
    void flagTile();
    bool isAFlag() const;
    void AddAdj(Tile* inTile);
    bool Revealed() const;

};