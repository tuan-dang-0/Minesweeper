#include "Board.h"
#include "Random.h"
#include <fstream>
#include <iostream>

Board::Board(){

    for(int i = 0; i < 3; i++)
        config[i] = 0;

    numTiles = 0;
    columns = 0;
    rows = 0;
    numMines = 0;
    gameLost = false;
    gameWon = false;
    isTestBoard = false;
    debugMode = false;

}

vector<string> Board::GetTestBoard(const string& boardName){
    vector<string> testBoard;
    ifstream inFile("boards/" + boardName);
    string line;
    while(getline(inFile, line))
        testBoard.push_back(line);
    return testBoard;
}

void Board::InitializeBoard(int config[3]){
    isTestBoard = false;

    for(int i = 0; i < 3; i++)
        this->config[i] = config[i];

    columns = config[0];
    rows = config[1];
    numMines = config[2];
    numTiles = columns * rows;

    InitializeTiles();
    SetupGame();
}

void Board::InitializeBoard(const string& boardName){
    isTestBoard = true;

    vector<string> testBoard = GetTestBoard(boardName);

    columns = testBoard[0].length();
    rows = testBoard.size();
    numTiles = columns * rows;

    InitializeTiles();

    int mineCount = 0;
    for(int i = 0; i < testBoard.size(); i++){
        for(int j = 0; j < testBoard[0].length(); j++){
            if(testBoard[i][j] == '1') {
                board[j][i].setMine();
                mineCount++;
            }
        }
    }
    numMines = mineCount;

    SetupGame();
}

void Board::InitializeTiles(){

    board.resize(columns);

    //Make 2D Tile Vector
    for(int i = 0; i < columns; i++)
        board[i] = vector<Tile>(rows);
}
void Board::SetupGame(){
    gameLost = false;
    gameWon = false;
    debugMode = false;
    SetupBoard();
    SetupMenu();
}

//Sets up the tiles and mines
void Board::SetupBoard(){
    //Initialize Tiles
    for(int i = 0; i < columns; i++){
        for(int j = 0; j < rows; j++) {
            board[i][j].SetPosition(i * 32, j * 32);
        }
    }

    if(!isTestBoard) {
        //Randomizes mines (setmine checks if it is already set or not, if not, then true)
        int tempCount = numMines;
        while (tempCount > 0) {
            if (board[Random::Int(0, columns - 1)][Random::Int(0, rows - 1)].setMine())
                tempCount--;
        }
    }

    GetAdj();

}

//Setups Bottom Bar Menu
void Board::SetupMenu(){
    //Smiley
    smiley = Smiley((columns * 32)/2 - 32, rows * 32);

    //Buttons
    buttons[0] = Button(columns * 32 - 256, smiley.GetyPos(), "debug");
    buttons[1] = Button(columns * 32 - 192, smiley.GetyPos(), "test_1");
    buttons[2] = Button(columns * 32 - 128, smiley.GetyPos(), "test_2");
    buttons[3] = Button(columns * 32 - 64, smiley.GetyPos(), "test_3");

    //Counter
    counter = Counter(0, smiley.GetyPos(), numMines);
}
//Draw board on window
void Board::Draw(sf::RenderWindow& window){

    //Draws Tiles
    for(int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            board[i][j].Draw(window);
            if(debugMode && !gameWon)
                board[i][j].DrawMine(window);
        }
    }

    //Draws Smiley
    smiley.Draw(window);

    //Draws Buttons
    for(int i = 0; i < 4; i++){
        buttons[i].Draw(window);
    }

    //Draws Counter
    counter.Draw(window);

}

//Reveals "Mine" tiles
void Board::RevealMines(){
    for(int i = 0; i < columns; i++){
        for(int j = 0; j < rows; j++) {
            if (board[i][j].isAMine()) {
                if (gameLost && !gameWon)
                    board[i][j].Reveal();

                if (gameWon)
                    board[i][j].flagTile();
            }
        }
    }
}

void Board::CheckLeftClicks(sf::RenderWindow& window){
    //Mouse position bb
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    //Gets bounds of each tile
    for(int i = 0; i < columns; i++){
        for(int j = 0; j < rows; j++){

            auto bounds = board[i][j].getGlobalBounds();

            if(bounds.contains(mousePos.x, mousePos.y) && !gameLost && !board[i][j].isAFlag() && !gameWon){
                board[i][j].Reveal();

                int revealedTiles = 0;
                for(int k = 0; k < columns; k++){
                    for(int l = 0; l < rows; l++){
                        if(board[k][l].Revealed())
                            revealedTiles++;
                    }
                }

                if(revealedTiles == numTiles - numMines){
                    gameWon = true;
                    smiley.SetWin();
                    RevealMines();
                    counter.GameWon();
                }

                if(board[i][j].isAMine()) {
                    gameLost = true;
                    RevealMines();
                    smiley.SetLose();
                }

            }
        }
    }

    //Smiley Click Functionality
    auto smileyBounds = smiley.getGlobalBounds();
    if(smileyBounds.contains(mousePos.x, mousePos.y)){
        gameLost = false;
        gameWon = false;
        InitializeBoard(config);
    }

    //Debug Button Functionality
    auto debugBounds = buttons[0].getGlobalBounds();
    if(!gameLost && !gameWon) {
        if (debugBounds.contains(mousePos.x, mousePos.y)) {
            debugMode = !debugMode;
        }
    }

    //Test Board Functionality
    for(int i = 1; i < 4; i++){
        auto buttonBounds = buttons[i].getGlobalBounds();
        if(buttonBounds.contains(mousePos.x, mousePos.y)){
            string name = "testboard";
            name += ('0' + i);
            name += ".brd";
            InitializeBoard(name);
        }
    }
}

void Board::CheckRightClicks(sf::RenderWindow& window){
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    //Flags tile if it is right clicked
    for(int i = 0; i < columns; i++){
        for(int j = 0; j < rows; j++){
            auto bounds = board[i][j].getGlobalBounds();

            if(bounds.contains(mousePos.x, mousePos.y) && !gameLost && !gameWon && !board[i][j].Revealed()){
                if(board[i][j].isAFlag())
                    counter.IncreaseCount();
                else
                    counter.DecreaseCount();
                board[i][j].flagTile();
            }
        }
    }
}

void Board::GetAdj(){
    for(int c = 0; c < columns; c++){
        for(int r = 0; r < rows; r++){
            for(int i = -1; i < 2; i++){
                for(int j = -1; j < 2; j++){
                    if(!(i == 0 && j == 0) &&
                    ((c + i < columns) && (c + i >= 0) && (r + j < rows) && (r + j >= 0))){
                        board[c][r].AddAdj(&board[c+i][r+j]);
                    }
                }
            }
        }
    }
};
