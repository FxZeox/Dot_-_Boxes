#include <iostream>
#include <string>
#include <cmath>
#include <limits>
#include <iomanip>
using namespace std;

const int MAX_MOVES = 100; // Maximum allowed moves to prevent infinite loops

const int SIZE_MIN = 2; // Minimum board size
const int SIZE_MAX = 8; // Maximum board size
int SIZE = 3; // Default size (3x3)
char board[SIZE_MAX][SIZE_MAX]; // To represent the boxes
bool horizontal[SIZE_MAX][SIZE_MAX + 1] = {false}; // To represent horizontal lines
bool vertical[SIZE_MAX + 1][SIZE_MAX] = {false}; // To represent vertical lines
int score[2] = {0, 0}; // Scores for Player A and Player B

void initializeBoard(int size) {
    SIZE = size;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';  // Empty board spaces
        }
    }
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printBoard() {
    clearScreen();
    cout << setw(10) << "--Dots and Boxes Game--\n\n"; 

    const string COLOR_RESET = "\033[0m";
    const string COLOR_PLAYER_A = "\033[37m"; 
    const string COLOR_PLAYER_B = "\033[37m"; 
    const string COLOR_BOARD = "\033[37m";    
    const string COLOR_DOT = "\033[37m";     

    cout << " ";
    for (int j = 0; j <= SIZE; j++) {
        cout << " " << j << "  ";
    }
    cout << endl;

    for (int i = 0; i <= SIZE; i++) {
        cout << i << " ";

        for (int j = 0; j <= SIZE; j++) {
            cout << COLOR_DOT << "*" << COLOR_RESET;
            if (j < SIZE) {
                if (horizontal[i][j]) {
                    cout << COLOR_BOARD << "\u2501\u2501\u2501" << COLOR_RESET;
                } else {
                    cout << "   ";
                }
            }
        }
        cout << endl;

        if (i < SIZE) {
            cout << "  ";
            for (int j = 0; j <= SIZE; j++) {
                if (vertical[i][j]) {
                    cout << COLOR_BOARD << "\u2503" << COLOR_RESET;
                } else {
                    cout << " ";
                }
                if (j < SIZE) {
                    if (board[i][j] == 'A') {
                        cout << COLOR_PLAYER_A << " " << board[i][j] << " " << COLOR_RESET;
                    } else if (board[i][j] == 'B') {
                        cout << COLOR_PLAYER_B << " " << board[i][j] << " " << COLOR_RESET;
                    } else {
                        cout << "   ";
                    }
                }
            }
            cout << endl;
        }
    }
}

bool isValidMove(int x1, int y1, int x2, int y2) {
    if (x1 < 0 || x1 > SIZE || y1 < 0 || y1 > SIZE ||
        x2 < 0 || x2 > SIZE || y2 < 0 || y2 > SIZE) {
        return false;
    }

    if (x1 == x2 && abs(y1 - y2) == 1) {
        int y = min(y1, y2);
        return !horizontal[x1][y];
    }
    else if (y1 == y2 && abs(x1 - x2) == 1) {
        int x = min(x1, x2);
        return !vertical[x][y1];
    }
    return false;
}

bool checkAndMarkBox(int x, int y, int player) {
    if (x >= 0 && x < SIZE && y >= 0 && y < SIZE &&
        horizontal[x][y] && horizontal[x + 1][y] &&
        vertical[x][y] && vertical[x][y + 1] &&
        board[x][y] == ' ') {
        board[x][y] = (player == 0) ? 'A' : 'B';
        score[player]++;
        return true;
    }
    return false;
}

void placeLine(int x1, int y1, int x2, int y2, int& player) {
    if (x1 == x2) {
        horizontal[x1][min(y1, y2)] = true;
    } else {
        vertical[min(x1, x2)][y1] = true;
    }

    bool boxCompleted = false;

    if (x1 == x2) {
        if (x1 > 0 && checkAndMarkBox(x1 - 1, min(y1, y2), player)) {
            boxCompleted = true;
        }
        if (x1 < SIZE && checkAndMarkBox(x1, min(y1, y2), player)) {
            boxCompleted = true;
        }
    } else {
        if (y1 > 0 && checkAndMarkBox(min(x1, x2), y1 - 1, player)) {
            boxCompleted = true;
        }
        if (y1 < SIZE && checkAndMarkBox(min(x1, x2), y1, player)) {
            boxCompleted = true;
        }
    }

    if (!boxCompleted) {
        player = 1 - player;
    }
}

bool isGameOver() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int size = 0;
    int moveCount = 0;

    while (true) {
        cout << "Choose board size (" << SIZE_MIN << "-" << SIZE_MAX << "): ";
        cin >> size;

        if (cin.fail() || size < SIZE_MIN || size > SIZE_MAX) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between " << SIZE_MIN << " and " << SIZE_MAX << "." << endl;
        } else {
            break;
        }
    }

    initializeBoard(size);
    int player = 0;

    while (!isGameOver() && moveCount < MAX_MOVES) {
        printBoard();
        cout << "Player " << (player == 0 ? 'A' : 'B') << ", enter your move (r1 c1 r2 c2) or 'q' to quit: ";

        string input;
        cin >> input;

        if (input == "q") {
            cout << "Exiting the game...\n";
            break;
        }

        int x1, y1, x2, y2;
        try {
            x1 = stoi(input);
            cin >> y1 >> x2 >> y2;

            if (cin.fail() || !isValidMove(x1, y1, x2, y2)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid move! Try again." << endl;
            } else {
                placeLine(x1, y1, x2, y2, player);
                moveCount++;
            }
        } catch (...) {
            cout << "Invalid input! Try again." << endl;
        }
    }

    printBoard();
    cout << "Game Over! Player A: " << score[0] << " points, Player B: " << score[1] << " points." << endl;
    if (score[0] > score[1]) {
        cout << "Player A wins!" << endl;
    } else if (score[0] < score[1]) {
        cout << "Player B wins!" << endl;
    } else {
        cout << "It's a tie!" << endl;
    }

    return 0;
}

