#include <iostream>
#include <string>
using namespace std;

// Constants
const int MAX_BOARD_SIZE = 13;

// Game board
char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int boardSize;

// Move history
int startXHistory[100], startYHistory[100];
int endXHistory[100], endYHistory[100];
int capturedXHistory[100], capturedYHistory[100];
char capturedPieceHistory[100];
int moveCount = 0;

// Current player (1 = attackers, 2 = defenders)
int currentPlayer = 1;

// Board setup and validation functions
void initializeBoard(int size);
void drawBoard();
bool isValidMove(int startX, int startY, int endX, int endY);
void checkCapture(int x, int y, int& capturedX, int& capturedY, char& capturedPiece);
bool checkVictory();
void makeMove(int startX, int startY, int endX, int endY);
void undoMove();

// Helper functions
void showHelp();
void showInfo();
void displayMenu();

// Main function
int main() {
    string menuChoice;
    bool gameRunning = true;

    while (gameRunning) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> menuChoice;

        if (menuChoice == "1") {
            // Start a new game
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
            // Quit the game
            cout << "Thank you for playing Viking Chess! Goodbye!" << endl;
            gameRunning = false;
        }
        else {
            cout << "Invalid choice! Please choose either 1 or 2." << endl;
        }
    }

    return 0;
}

// Initialize the board
void initializeBoard(int size) {
    boardSize = size;
    int center = size / 2;

    // Fill the board with empty spaces
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = '.';
        }
    }

    // Place the king
    board[center][center] = 'K';

    // Place defenders around the king
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

    // Place attackers
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

// Draw the board
void drawBoard() {
    cout << "  ";
    for (int i = 0; i < boardSize; i++) cout << i << " ";
    cout << endl;
    for (int i = 0; i < boardSize; i++) {
        cout << i << " ";
        for (int j = 0; j < boardSize; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Validate move
bool isValidMove(int startX, int startY, int endX, int endY) {
    if (startX < 0 || startX >= boardSize || startY < 0 || startY >= boardSize ||
        endX < 0 || endX >= boardSize || endY < 0 || endY >= boardSize) {
        return false;
    }

    // Check if the destination is one of the corners or the center
    if ((endX == boardSize / 2 && endY == boardSize / 2) ||
        (endX == 0 && endY == 0) ||
        (endX == 0 && endY == boardSize - 1) ||
        (endX == boardSize - 1 && endY == 0) ||
        (endX == boardSize - 1 && endY == boardSize - 1)) {
        return false;
    }

    // Check if the starting cell is empty or the destination is not empty
    if (board[startX][startY] == '.' || board[endX][endY] != '.') {
        return false;
    }

    // Check if the move is either vertical or horizontal
    if (startX != endX && startY != endY) {
        return false;
    }

    // Check if the path is clear for vertical movement
    if (startX == endX) {
        for (int i = min(startY, endY) + 1; i < max(startY, endY); i++) {
            if (board[startX][i] != '.') return false;
        }
    }
    // Check if the path is clear for horizontal movement
    else {
        for (int i = min(startX, endX) + 1; i < max(startX, endX); i++) {
            if (board[i][startY] != '.') return false;
        }
    }

    return true;
}

// Check for capture
void checkCapture(int x, int y, int& capturedX, int& capturedY, char& capturedPiece) {
    const int dx[] = { -1, 1, 0, 0 };
    const int dy[] = { 0, 0, -1, 1 };
    char opponent = (currentPlayer == 1 ? 'D' : 'A');

    capturedX = -1; // No captured piece by default
    capturedY = -1;
    capturedPiece = '.';

    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        int nnx = x + 2 * dx[d], nny = y + 2 * dy[d];
        if (nx >= 0 && nx < boardSize && ny >= 0 && ny < boardSize &&
            nnx >= 0 && nnx < boardSize && nny >= 0 && nny < boardSize) {
            if (board[nx][ny] == opponent && board[nnx][nny] == board[x][y]) {
                capturedX = nx;
                capturedY = ny;
                capturedPiece = board[nx][ny];
                board[nx][ny] = '.';
                cout << "Piece at (" << nx << ", " << ny << ") was captured!" << endl;
            }
        }
    }
}

// Check for victory
bool checkVictory() {
    const int corners[4][2] = { {0, 0}, {0, boardSize - 1}, {boardSize - 1, 0}, {boardSize - 1, boardSize - 1} };
    for (int i = 0; i < 4; i++) {
        int cx = corners[i][0], cy = corners[i][1];
        if (board[cx][cy] == 'K') {
            cout << "Defenders win!" << endl;
            return true;
        }
    }

    // Check if the king is surrounded by attackers
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == 'K') {
                const int dx[] = { -1, 1, 0, 0 };
                const int dy[] = { 0, 0, -1, 1 };
                bool surrounded = true;

                for (int d = 0; d < 4; d++) {
                    int nx = i + dx[d], ny = j + dy[d];
                    if (nx >= 0 && nx < boardSize && ny >= 0 && ny < boardSize) {
                        if (board[nx][ny] != 'A') {
                            surrounded = false;
                            break;
                        }
                    }
                    else {
                        surrounded = false;
                        break;
                    }
                }

                if (surrounded) {
                    cout << "Attackers win! The king has been captured!" << endl;
                    return true;
                }
            }
        }
    }

    return false;
}

// Make a move
void makeMove(int startX, int startY, int endX, int endY) {
    if (!isValidMove(startX, startY, endX, endY)) {
        cout << "Invalid move!" << endl;
        return;
    }

    char piece = board[startX][startY];
    board[endX][endY] = piece;
    board[startX][startY] = '.';

    int capturedX, capturedY;
    char capturedPiece;
    checkCapture(endX, endY, capturedX, capturedY, capturedPiece);

    // Record move history
    startXHistory[moveCount] = startX;
    startYHistory[moveCount] = startY;
    endXHistory[moveCount] = endX;
    endYHistory[moveCount] = endY;
    capturedXHistory[moveCount] = capturedX;
    capturedYHistory[moveCount] = capturedY;
    capturedPieceHistory[moveCount] = capturedPiece;
    moveCount++;

    if (checkVictory()) exit(0);
    currentPlayer = 3 - currentPlayer;
}

// Undo the last move
void undoMove() {
    if (moveCount == 0) {
        cout << "No moves to undo!" << endl;
        return;
    }

    moveCount--;
    int startX = startXHistory[moveCount];
    int startY = startYHistory[moveCount];
    int endX = endXHistory[moveCount];
    int endY = endYHistory[moveCount];
    int capturedX = capturedXHistory[moveCount];
    int capturedY = capturedYHistory[moveCount];
    char capturedPiece = capturedPieceHistory[moveCount];

    board[startX][startY] = board[endX][endY];
    board[endX][endY] = '.';

    if (capturedX != -1) {
        board[capturedX][capturedY] = capturedPiece;
    }

    currentPlayer = 3 - currentPlayer;
}

// Show help
void showHelp() {
    cout << "Commands:\n";
    cout << "  move x1 y1 x2 y2 - move a piece from (x1, y1) to (x2, y2)\n";
    cout << "  back - undo the last move\n";
    cout << "  info - show current game information\n";
    cout << "  help - show this help menu\n";
    cout << "  quit - quit the game\n";
}

// Show game info
void showInfo() {
    cout << "Player " << (currentPlayer == 1 ? "Attackers" : "Defenders") << "'s turn.\n";
}

// Display main menu
void displayMenu() {
    cout << "\nViking Chess - Tafl\n";
    cout << "1. Start a New Game\n";
    cout << "2. Quit\n";
}