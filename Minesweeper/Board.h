#pragma once
#include "Tile.h"
#include "Smiley.h"
#include "Button.h"
#include "Counter.h"
using namespace std;

class Board{
    int config[3]; // columns, rows, numMines
    int columns;
    int rows;
    int numMines;
    int numTiles;
    vector<vector<Tile>> board;
    Smiley smiley;
    Button buttons[4];
    Counter counter;
    bool gameLost;
    bool debugMode;
    bool gameWon;
    bool isTestBoard;

public:
    Board();
    vector<string> GetTestBoard(const string& boardName);
    void InitializeBoard(int config[3]);
    void InitializeBoard(const string& boardName);
    void InitializeTiles();
    void SetupGame();
    void SetupBoard();
    void SetupMenu();
    void Draw(sf::RenderWindow& window);
    void RevealMines();
    void CheckLeftClicks(sf::RenderWindow& window);
    void CheckRightClicks(sf::RenderWindow& window);
    void GetAdj();
};