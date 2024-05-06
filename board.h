#include <fstream>
#include "block.h"

class Board {
public:
    Board() { };
    Board(int boardSize);

    // Accessors
    int getBoardSize();
    Block** getBlockArray();
    int** getBombMap();
    // Mutators
    void setBombMap(int curRow, int curCol, int value);
    void setBlockArray(int curRow, int curCol, int value); 

    bool isWithin(int row, int col);

private:
    int** bombMap;
    Block** blockArray;
    int boardSize;
};

Board::Board(int boardSize) : boardSize(boardSize) {
    blockArray = new Block* [boardSize];
    bombMap = new int* [boardSize];
    /* Your code needs to start here*/
    /* You need to make blockArray, bombMap initialize*/

};

int Board::getBoardSize() {
    /* Your code needs to start here*/
    // return the board size
    return boardSize;
}

Block** Board::getBlockArray() {
    /* Your code needs to start here*/
    // return the Block array 
    return blockArray;
}

int** Board::getBombMap() {
    /* Your code needs to start here*/
    // return the bomb map (how bomb damaged on the turn)
    return bombMap;
}

void Board::setBombMap(int curRow, int curCol, int value) {
    /* Your code needs to start here*/
    // change the bombmap values bombMap[curRow][curCol] to value
    bombMap[curRow][curCol] = value;
    return;
}

void Board::setBlockArray(int curRow, int curCol, int value) {
    /* Your code needs to start here*/
    // change the blockarray values blockArray[curRow][curCol] to value
    blockArray[curRow][curCol].setHeight(value);
    return;
}

bool Board::isWithin(int row, int col) {
    // check whether the point is within the board
    if((0 <= row) && (row < boardSize) && (0 <= col) && (col < boardSize)) {
        return true;
    } else {
        return false;
    }
}