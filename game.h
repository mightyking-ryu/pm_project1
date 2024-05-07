#include <cstdio>
#include <iostream>

#include "player.h"
#include "board.h"

using namespace std;

class Game {
public:
    Game(int gameMode); 
    void turnPass();
    void printBoard();
    void printBombMap();
    bool move(int newRow, int newCol);
    void bomb(int bombType, int depth);
    bool checkEndCondition();
    bool canYangMove();
    bool canYangMoveTo(int, int);
    bool canGangMove();
    bool canGangMoveTo(int, int);
    void bomb0(int, int, int);
    void bomb1(int, int, int);
    void bomb2(int, int, int);
    void bomb3(int, int, int);

    // Mutators (setters)
    void setTurn(int nextTurn);
    void setBoard(int gameMode);

    // Accessors (getters)
    int getTurn();
    int getWinner();
    Board getBoard();
    Player getYang();
    Player getGang();

private:
    const int MAX_TURN = 20;
    int gameMode;
    int turn;
    Board mainGameBoard;
    Player Yang;
    Player Gang;
    int winner;
};

Game::Game(int gameMode) : gameMode(gameMode) {
    Game::setTurn(0);
    Game::setBoard(gameMode);
    // Set the player initialization
    Yang = Player(0,0);
    Gang = Player(mainGameBoard.getBoardSize()-1, mainGameBoard.getBoardSize()-1);
    return;
}

int Game::getTurn() { 
    return turn;
}

Player Game::getGang() {
    return Gang;
}

Player Game::getYang() {
    return Yang;
}

Board Game::getBoard() {
    return mainGameBoard;
}

int Game::getWinner() {
    return winner;
}

void Game::turnPass() {
    setTurn(turn + 1);
    return; 
}

void Game::printBoard() {
    /* Change this code as you need */
    /* Do not break empty blocks for foramt or endl */

    for(int i=0;i<mainGameBoard.getBoardSize();i++){
        for(int j=0;j<mainGameBoard.getBoardSize();j++){
            if (Yang.getRow() == i && Yang.getCol() == j){
                cout << 'Y' << " ";
            }
            else if (Gang.getRow() == i && Gang.getCol() == j){
                cout << 'G' << " ";
            }
            else {
                cout << mainGameBoard.getBlockArray()[i][j].getHeight() << " ";
            }
        }
        cout << endl;
    }
}

void Game::setTurn(int nextTurn){
    // Set the turn functions
    turn = nextTurn;
    return; 
}

void Game::setBoard(int gameMode){
    // Game mode dependent
    if (gameMode == 1){
        mainGameBoard = Board(9);

    }
    else if(gameMode == 2){
        mainGameBoard = Board(15);
    }

    else if(gameMode == 3){
        mainGameBoard = Board(21);
    }

    else if(gameMode == 4){
        mainGameBoard = Board(27);
    }

    else {
        cout << "Game mode not expected number input";
    }    
    return; 
}

bool Game::move(int newRow, int newCol){
    /* Your code needs to start here*/
    /*
    Movement
    Yang: Chess knight
    Gang: Directly Around (8-direction)

    Please refer to the slide for each movement

    if newRow, newCol that user gives are not available, return false
    else, move the Player and set to the newRow, newCol. Then return true
    
    */
    if (turn % 2 == 0) {
        // Yang turn
        if (canYangMoveTo(newRow, newCol)) {
            Yang.setRow(newRow);
            Yang.setCol(newCol);
            return true;
        } else {
            return false;
        }
    } else {
        // Gang turn
        if (canGangMoveTo(newRow, newCol)) {
            Gang.setRow(newRow);
            Gang.setCol(newCol);
            return true;
        } else {
            return false;
        }
    }

}

bool Game::checkEndCondition(){
    /* Your code needs to start here*/
    /* 
    You need to check conditions to decide whether the game ended or not

    1) A player reached the ground(0)
    2) A player cannot move anymore
    3) The turn reached MAX_TURN(20)

    If the both of the player reach to the end condition
    We need to compare the score

    If the game ended we need to set winner at here
    -1: Draw
    0: Yang win
    1: Gang win
    */

    bool isYangEnd = false;
    bool isGangEnd = false;

    if ((mainGameBoard.getBlockArray()[Yang.getRow()][Yang.getCol()].getHeight() < 1) || (!canYangMove())) {
        isYangEnd = true;
    }
    if ((mainGameBoard.getBlockArray()[Gang.getRow()][Gang.getCol()].getHeight() < 1) || (!canGangMove())) {
        isGangEnd = true;
    }
    if (turn == 20) {
        isYangEnd = true;
        isGangEnd = true;
    }

    if (isYangEnd && isGangEnd) {
        // compare score
        int yangScore = Yang.getScore();
        int gangScore = Gang.getScore();
        if (yangScore > gangScore) {
            winner = 0;
        } else if (yangScore < gangScore) {
            winner = 1;
        } else {
            winner = -1;
        }
        return true;
    } else if (isYangEnd && !isGangEnd) {
        // Gang win
        winner = 1;
        return true;
    } else if (!isYangEnd && isGangEnd) {
        // Yang win
        winner = 0;
        return true;
    } else {
        // not ended
        return false;
    }
}

void Game::bomb(int bombType, int depth){
    /* Your code needs to start here*/
    /* Implement each bomb type and modify the board accordingly*/
    /*
    bomb type 0: square 
    bomb type 1: Recursively calling left, top, right, down
    bomb type 2: Recurisvely calling but diagonal
    bomb type 3: Recursively calling left, top, right, down but, damage 1

    Please refer to the slide for each bomb type

    After bomb function, mainBoard should be modified accordingly
    Also, the score should be updated after bomb damage
    
    If depth <= 0 just return 
    (Do nothing. It will be regarded as passing the turn)
    */

    int curBoardSize = mainGameBoard.getBoardSize();
    int curRow;
    int curCol;
    if (turn % 2 == 0) {
        curRow = Yang.getRow();
        curCol = Yang.getCol();
    } else {
        curRow = Gang.getRow();
        curCol = Gang.getCol();
    }

    // initialize bombMap to 0
    for(int i = 0; i < curBoardSize; i++) {
        for(int j = 0; j < curBoardSize; j++) {
            mainGameBoard.setBombMap(i, j, 0);
        }
    }
    // update bombMap
    if (depth <= 0) {
        return;
    } else {
        switch(bombType) {
            case 0:
                bomb0(curRow, curCol, depth);
                break;
            case 1:
                bomb1(curRow, curCol, depth);
                break;
            case 2:
                bomb2(curRow, curCol, depth);
                break;
            case 3:
                bomb3(curRow, curCol, depth);
                break;
            default:
                return;
        }
    }
    // update block height & update player score
    int score = 0;
    for(int i = 0; i < curBoardSize; i++) {
        for(int j = 0; j < curBoardSize; j++) {
            int bombed = mainGameBoard.getBombMap()[i][j];
            if (bombed == 0) {
                continue;
            } else {
                int curHeight = mainGameBoard.getBlockArray()[i][j].getHeight();
                if (curHeight >= bombed) {
                    mainGameBoard.getBlockArray()[i][j].setHeight(curHeight - bombed);
                    score += bombed;
                } else {
                    mainGameBoard.getBlockArray()[i][j].setHeight(0);
                    score += curHeight;
                }
            }
        }
    }
    if (turn % 2 == 0) {
        Yang.setScore(Yang.getScore() + score);
    } else {
        Gang.setScore(Gang.getScore() + score);
    }
    return;
}

void Game::printBombMap(){
    /* Change this code as you need */
    /* Do not break empty blocks for foramt or endl */
    int curBoardSize = mainGameBoard.getBoardSize();
    for(int i=0;i<curBoardSize; i++){
        for(int j=0;j<curBoardSize; j++){
            if (mainGameBoard.getBombMap()[i][j] > 0){
                cout << mainGameBoard.getBombMap()[i][j] << " ";
            }
            else {
                cout << 0 << " ";
            }
        }
        cout << "          " ;

        for(int j=0;j<curBoardSize; j++){
            if (Yang.getRow() == i && Yang.getCol() == j){
                cout << 'Y' << " ";
            }
            else if (Gang.getRow() == i && Gang.getCol() == j){
                cout << 'G' << " ";
            }
            else {
                cout << mainGameBoard.getBlockArray()[i][j].getHeight() << " ";
            }
        }
        cout << endl;
    }
    return;
}

bool Game::canYangMoveTo(int newRow, int newCol) {
    // check whether Yang can move to block (newRow, newCol)

    // check movement
    int rowDiff = newRow - Yang.getRow();
    int colDiff = newCol - Yang.getCol();
    switch(rowDiff) {
        case 1:
        case -1:
            switch(colDiff) {
                case 2:
                case -2:
                    break;
                default:
                    return false;
            }
            break;
        case 2:
        case -2:
            switch(colDiff) {
                case 1:
                case -1:
                    break;
                default:
                    return false;
            }
            break;
        default:
            return false;
    }
    // check within
    if(!mainGameBoard.isWithin(newRow, newCol)) {
        return false;
    }
    // check height
    if(mainGameBoard.getBlockArray()[newRow][newCol].getHeight() < 1) {
        return false;
    }
    // check Gang
    if(newRow == Gang.getRow() && newCol == Gang.getCol()) {
        return false;
    }
    return true;
}

bool Game::canGangMoveTo(int newRow, int newCol) {
    // check whether Gang can move to block (newRow, newCol)

    // check movement
    int rowDiff = newRow - Gang.getRow();
    int colDiff = newCol - Gang.getCol();
    switch(rowDiff) {
        case 1:
        case -1:
            switch(colDiff) {
                case 1:
                case -1:
                case 0:
                    break;
                default:
                    return false;
            }
            break;
        case 0:
            switch(colDiff) {
                case 1:
                case -1:
                    break;
                default:
                    return false;
            }
            break;
        default:
            return false;
    }
    // check within
    if(!mainGameBoard.isWithin(newRow, newCol)) {
        return false;
    }
    // check height
    if(mainGameBoard.getBlockArray()[newRow][newCol].getHeight() < 1) {
        return false;
    }
    // check Yang
    if(newRow == Yang.getRow() && newCol == Yang.getCol()) {
        return false;
    }
    return true;
}

bool Game::canYangMove() {
    // check whether Yang can move
    int curRow = Yang.getRow();
    int curCol = Yang.getRow();
    if(canYangMoveTo(curRow+1, curCol+2)) {
        return true;
    }else if(canYangMoveTo(curRow+1, curCol-2)){
        return true;
    }else if(canYangMoveTo(curRow-1, curCol+2)){
        return true;
    }else if(canYangMoveTo(curRow-1, curCol-2)){
        return true;
    }else if(canYangMoveTo(curRow+2, curCol+1)){
        return true;
    }else if(canYangMoveTo(curRow+2, curCol-1)){
        return true;
    }else if(canYangMoveTo(curRow-2, curCol+1)){
        return true;
    }else if(canYangMoveTo(curRow-2, curCol-1)){
        return true;
    }else {
        return false;
    }
}

bool Game::canGangMove() {
    // check whether Gang can move
    int curRow = Gang.getRow();
    int curCol = Gang.getRow();
    if(canGangMoveTo(curRow+1, curCol+1)) {
        return true;
    }else if(canGangMoveTo(curRow+1, curCol)){
        return true;
    }else if(canGangMoveTo(curRow+1, curCol-1)){
        return true;
    }else if(canGangMoveTo(curRow-1, curCol+1)){
        return true;
    }else if(canGangMoveTo(curRow-1, curCol)){
        return true;
    }else if(canGangMoveTo(curRow-1, curCol-1)){
        return true;
    }else if(canGangMoveTo(curRow, curCol+1)){
        return true;
    }else if(canGangMoveTo(curRow, curCol-1)){
        return true;
    }else {
        return false;
    }
}

void Game::bomb0(int curRow, int curCol, int depth) {
    for(int i = curRow-depth+1; i < curRow+depth; i++) {
        for(int j = curCol-depth+1; j < curCol+depth; j++) {
            if (mainGameBoard.isWithin(i, j)) {
                if (mainGameBoard.getBombMap()[i][j] < depth) {
                    mainGameBoard.getBombMap()[i][j] = depth;
                }
            }
        }
    }
    return;
}
void Game::bomb1(int curRow, int curCol, int depth) {
    bomb0(curRow, curCol, depth);
    if (depth <= 1) {
        return;
    } else {
        int diff = 2*depth -2;
        bomb1(curRow+diff, curCol, depth-1);
        bomb1(curRow-diff, curCol, depth-1);
        bomb1(curRow, curCol+diff, depth-1);
        bomb1(curRow, curCol-diff, depth-1);
    }
    return;
}
void Game::bomb2(int curRow, int curCol, int depth) {
    return;
}
void Game::bomb3(int curRow, int curCol, int depth) {
    return;
}