#include <SFML/Graphics.hpp> // hpp == .h, but specifically a C++ only header file
#include <iostream>
#include <fstream>
#include "Tile.h"
#include "Board.h"
#include "Random.h"
using namespace std;

//41:18 SFML code example, creating classes

void getConfig(const string& fileName, int array[3]);

int main(){
    int info [3]; // columns, rows, mines

    getConfig("boards/config.cfg", info);

    sf::RenderWindow window(sf::VideoMode(info[0] * 32, info[1] * 32  + 88), "MineSweeper");

    Board board;
    board.InitializeBoard(info);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    board.CheckLeftClicks(window);
                }

                if(event.mouseButton.button == sf::Mouse::Right){
                    board.CheckRightClicks(window);
                }
            }
        }
        window.clear();
        board.Draw(window);
        window.display();
    }

    return 0;
}

void getConfig(const string& fileName, int array[3]) {
    ifstream inFile(fileName);

    if (inFile.is_open()) {
        string line;
        for (int i = 0; i < 3; i++) {
            getline(inFile, line);
            array[i] = stoi(line);
        }
    } else
        cout << "Yo es not open" << endl;
}