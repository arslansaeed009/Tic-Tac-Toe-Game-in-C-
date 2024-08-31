#include <iostream>
#include <vector>

using namespace std;

const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

class TicTacToe {
public:
    TicTacToe();
    void run();

private:
    vector<vector<char>> board;
    char currentPlayer;
    bool gameOver;

    void printBoard();
    void switchPlayer();
    bool makeMove(int row, int col);
    bool checkWin();
    bool checkDraw();
    void handlePlayerMove();
    void handleComputerMove();
    void checkGameStatus();
};

TicTacToe::TicTacToe() : board(3, vector<char>(3, EMPTY)), currentPlayer(PLAYER_X), gameOver(false) {}

void TicTacToe::printBoard() {
    cout << "  0 1 2\n";
    for (int row = 0; row < 3; ++row) {
        cout << row << " ";
        for (int col = 0; col < 3; ++col) {
            cout << board[row][col];
            if (col < 2) cout << "|";
        }
        cout << endl;
        if (row < 2) cout << "  -----\n";
    }
    cout << endl;
}

void TicTacToe::switchPlayer() {
    currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
}

bool TicTacToe::makeMove(int row, int col) {
    if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != EMPTY) {
        return false;
    }
    board[row][col] = currentPlayer;
    return true;
}

bool TicTacToe::checkWin() {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) ||
            (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
        (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)) {
        return true;
    }
    return false;
}

bool TicTacToe::checkDraw() {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (board[row][col] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

void TicTacToe::handlePlayerMove() {
    int row, col;
    cout << "Player " << currentPlayer << ", enter your move (row and column): ";
    cin >> row >> col;
    while (!makeMove(row, col)) {
        cout << "Invalid move. Try again: ";
        cin >> row >> col;
    }
}

void TicTacToe::handleComputerMove() {
    // Simple computer move: choose the first empty spot
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (board[row][col] == EMPTY) {
                board[row][col] = currentPlayer;
                return;
            }
        }
    }
}

void TicTacToe::checkGameStatus() {
    if (checkWin()) {
        printBoard();
        cout << "Player " << currentPlayer << " wins!" << endl;
        gameOver = true;
    } else if (checkDraw()) {
        printBoard();
        cout << "The game is a draw!" << endl;
        gameOver = true;
    }
}

void TicTacToe::run() {
    cout << "Welcome to Tic-Tac-Toe!\n";
    while (!gameOver) {
        printBoard();
        if (currentPlayer == PLAYER_X) {
            handlePlayerMove();
        } else {
            handleComputerMove();
        }
        checkGameStatus();
        if (!gameOver) {
            switchPlayer();
        }
    }
}

int main() {
    TicTacToe game;
    game.run();
    return 0;
}
