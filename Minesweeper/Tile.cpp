#include "Tile.h"
Tile::Tile(){
    hiddenTile.setTexture(TextureManager::GetTexture("tile_hidden"));
    revealedTile.setTexture(TextureManager::GetTexture("tile_revealed"));
    mine.setTexture(TextureManager::GetTexture("mine"));
    flag.setTexture(TextureManager::GetTexture("flag"));
    isRevealed = false;
    isMine = false;
    isFlagged = false;
    numAdjMines = 0;
}

void Tile::Draw(sf::RenderWindow& window){

    if(isRevealed){
        window.draw(revealedTile);
        if(numAdjMines > 0)
            window.draw(num);

        if(isFlagged)
            window.draw(flag);

        DrawMine(window);
    }
    else{
        window.draw(hiddenTile);
        if(isFlagged)
            window.draw(flag);
    }

}

void Tile::DrawMine(sf::RenderWindow& window){
    if(isMine)
        window.draw(mine);
}

void Tile::Reveal(){
    isRevealed = true;
    if(!isMine) {
        for (int i = 0; i < adjacent.size(); i++) {
            if (!adjacent[i]->isAMine() && !adjacent[i]->Revealed() && !adjacent[i]->isAFlag() && numAdjMines == 0)
                adjacent[i]->Reveal();
        }
    }
}

void Tile::SetPosition(float x, float y){
    hiddenTile.setPosition(x, y);
    revealedTile.setPosition(x, y);
    mine.setPosition(x, y);
    flag.setPosition(x, y);
    num.setPosition(x, y);
}

bool Tile::setMine(){
    if(!isMine) {
        isMine = true;
        return true;
    }
    else
        return false;
}

bool Tile::isAMine() const{
    if(isMine)
        return true;
    else
        return false;
}
sf::Rect<float> Tile::getGlobalBounds(){
    return hiddenTile.getGlobalBounds();
}

void Tile::flagTile(){
    isFlagged = !isFlagged;
}

bool Tile::isAFlag() const{
    return isFlagged;
}

void Tile::AddAdj(Tile* inTile){
    adjacent.push_back(inTile);

    if(inTile->isAMine())
        numAdjMines++;

    if(!isAMine()) {
        string textureName = "number_";
        textureName += '0' + numAdjMines;
        if (numAdjMines > 0)
            num.setTexture(TextureManager::GetTexture(textureName));
    }
}

bool Tile::Revealed() const{
    return isRevealed;
}