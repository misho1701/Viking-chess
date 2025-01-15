#include <iostream>
#include <string>
using namespace std;

const int MAX_BOARD_SIZE = 13;


char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int boardSize;


int startXHistory[100], startYHistory[100];
int endXHistory[100], endYHistory[100];
int capturedXHistory[100], capturedYHistory[100];
char capturedPieceHistory[100];
int moveCount = 0;


int currentPlayer = 1;


void initializeBoard(int size);
void drawBoard();
bool isValidMove(int startX, int startY, int endX, int endY);
void checkCapture(int x, int y, int& capturedX, int& capturedY, char& capturedPiece);
bool checkVictory();
void makeMove(int startX, int startY, int endX, int endY);
void undoMove();


void showHelp();
void showInfo();
void displayMenu();


int main() {
    string menuChoice;
    bool gameRunning = true;

    while (gameRunning) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> menuChoice;

        if (menuChoice == "1") {
            
            cout << "Enter board size (7 to 13): ";
            cin >> boardSize;

            if (boardSize < 7 || boardSize > 13) {
                cout << "Invalid board size!" << endl;
                continue;
            }

            initializeBoard(boardSize);

            while (true) {
                drawBoard();
                cout << "Player " << (currentPlayer == 1 ? "Attackers" : "Defenders") << ", enter a command: ";
                string command;
                cin >> command;

                if (command == "move") {
                    int startX, startY, endX, endY;
                    cin >> startX >> startY >> endX >> endY;
                    makeMove(startX, startY, endX, endY);
                }
                else if (command == "back") {
                    undoMove();
                }
                else if (command == "help") {
                    showHelp();
                }
                else if (command == "info") {
                    showInfo();
                }
                else if (command == "quit") {
                    break;
                }
                else {
                    cout << "Invalid command! Use 'help' for a list of commands." << endl;
                }
            }
        }
        else if (menuChoice == "2") {
            
            cout << "Thank you for playing Viking Chess! Goodbye!" << endl;
            gameRunning = false;
        }
        else {
            cout << "Invalid choice! Please choose either 1 or 2." << endl;
        }
    }

    return 0;
}


void initializeBoard(int size) {
    boardSize = size;
    int center = size / 2;

    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = '.';
        }
    }

    
    board[center][center] = 'K';

    
    board[center - 1][center] = 'D';
    board[center + 1][center] = 'D';
    board[center][center - 1] = 'D';
    board[center][center + 1] = 'D';

    if (size >= 9) {
        board[center - 2][center] = 'D';
        board[center + 2][center] = 'D';
        board[center][center - 2] = 'D';
        board[center][center + 2] = 'D';
    }

    
    for (int i = 2; i < size - 2; i++) {
        board[0][i] = 'A';
        board[size - 1][i] = 'A';
        board[i][0] = 'A';
        board[i][size - 1] = 'A';
    }

    board[center][1] = 'A';
    board[center][size - 2] = 'A';
    board[1][center] = 'A';
    board[size - 2][center] = 'A';
}


