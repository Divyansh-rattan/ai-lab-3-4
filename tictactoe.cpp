#include <iostream>
#include <vector>
#include <limits>
using namespace std;

vector<int> board(10, 2);
int turn = 1;
bool aiIsX;

void printBoard() {
    cout << "\n";
    for (int i = 1; i <= 9; ++i) {
        char mark = (board[i] == 3) ? 'X' : (board[i] == 5) ? 'O' : ' ';
        cout << " " << mark << " ";
        if (i % 3 == 0) cout << "\n";
        else cout << "|";
    }
    cout << "\n";
}

int checkWinner() {
    vector<vector<int>> lines = {
        {1,2,3}, {4,5,6}, {7,8,9},
        {1,4,7}, {2,5,8}, {3,6,9},
        {1,5,9}, {3,5,7}
    };

    for (auto &line : lines) {
        int prod = board[line[0]] * board[line[1]] * board[line[2]];
        if (prod == 27) return 3;   // X wins
        if (prod == 125) return 5;  // O wins
    }
    return 0;
}

bool isFull() {
    for (int i = 1; i <= 9; i++) {
        if (board[i] == 2) return false;
    }
    return true;
}

int minimax(bool isMaximizing, int depth, int aiSymbol, int humanSymbol) {
    int winner = checkWinner();
    if (winner == aiSymbol) return 10 - depth;
    if (winner == humanSymbol) return depth - 10;
    if (isFull()) return 0;

    if (isMaximizing) {
        int best = numeric_limits<int>::min();
        for (int i = 1; i <= 9; i++) {
            if (board[i] == 2) {
                board[i] = aiSymbol;
                int score = minimax(false, depth + 1, aiSymbol, humanSymbol);
                board[i] = 2;
                best = max(best, score);
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int i = 1; i <= 9; i++) {
            if (board[i] == 2) {
                board[i] = humanSymbol;
                int score = minimax(true, depth + 1, aiSymbol, humanSymbol);
                board[i] = 2;
                best = min(best, score);
            }
        }
        return best;
    }
}

void aiMove() {
    int aiSymbol = aiIsX ? 3 : 5;
    int humanSymbol = aiIsX ? 5 : 3;
    int bestScore = numeric_limits<int>::min();
    int move = 0;

    for (int i = 1; i <= 9; i++) {
        if (board[i] == 2) {
            board[i] = aiSymbol;
            int score = minimax(false, 0, aiSymbol, humanSymbol);
            board[i] = 2;
            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }

    cout << "AI chooses square " << move << "\n";
    board[move] = aiSymbol;
    turn++;
}

void humanMove() {
    int move;
    while (true) {
        cout << "Your move (1-9): ";
        cin >> move;
        if (move >= 1 && move <= 9 && board[move] == 2) {
            board[move] = (turn % 2 == 1) ? 3 : 5;
            turn++;
            break;
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }
}

int main() {
    cout << "Welcome to Tic-Tac-Toe with Minimax!\n";
    char choice;
    cout << "Should AI play as X and start first? (y/n): ";
    cin >> choice;
    aiIsX = (choice == 'y' || choice == 'Y');

    printBoard();

    while (turn <= 9) {
        if ((turn % 2 == 1) == aiIsX) {
            aiMove();
        } else {
            humanMove();
        }

        printBoard();

        int winner = checkWinner();
        if (winner == 3) { // X wins
            cout << ((aiIsX && winner == 3) ? "AI wins!\n" : (!aiIsX && winner == 3) ? "AI wins!\n" : "Human wins!\n");
            return 0;
        } else if (winner == 5) { // O wins
            cout << ((aiIsX && winner == 5) ? "AI wins!\n" : (!aiIsX && winner == 5) ? "AI wins!\n" : "Human wins!\n");
            return 0;
        }
    }

    cout << "It's a draw!\n";
    return 0;
}
