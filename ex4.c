/******************
Name: Maya Mattar
ID: 213510407
Assignment: ex4
*******************/
#include <stdio.h>
#include <string.h>

#define STACK_SIZE 100 // Parenthesis Validator
#define MAX_INPUT_SIZE 100
#define MAX 20 // Maximum board size (Queens Battle)
#define MAX_AREAS 256
// Prototypes for all functions
void task1RobotPaths();
int calculatePaths(int column, int row);
void task2HumanPyramid();
float calculateWeight(int row, int column, float weights[]);
void task3ParenthesisValidator();
int validateRecursiveHelper(char input[], int index, char stack[], int top);
int isMatch(char open, char close);
int validateRecursive();
void task4QueensBattle();
int solveQueens(int row, char board[MAX][MAX], int boardSize, int cols[MAX], int areas[MAX_AREAS]);
int isSafe(int row, int col, char board[MAX][MAX], int boardSize);
void printSolution(char board[MAX][MAX], int boardSize);

int main() {
    int task = -1;
    do {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Exit\n");

        if (scanf("%d", &task)) { // To make sure the input is an integer
            switch (task) {
                case 1:
                    task1RobotPaths();
                    break;
                case 2:
                    task2HumanPyramid();
                    break;
                case 3:
                    task3ParenthesisValidator();
                    break;
                case 4:
                    task4QueensBattle();
                    break;
                case 5:
                    printf("Goodbye!\n");
                    break;
                default:
                    printf("Please choose a task number from the list.\n");
                    break;
            }
        } else {
            scanf("%*s"); // To discard the invalid input
            printf("Please choose a task number from the list.\n");
        }
    } while (task != 5);
}
// Function for Task 1: Robot Paths
void task1RobotPaths() {
    int column, row;
    // Prompt user for input
    printf("Please enter the coordinates of the robot (column, row): \n");
    scanf("%d %d", &column, &row);
    // Validate input
    if (column < 0 || row < 0) {
        printf("The total number of paths the robot can take to reach home is: 0\n");
        return;
    }
    // Calculate and print the number of paths
    int totalPaths = calculatePaths(column, row);
    printf("The total number of paths the robot can take to reach home is: %d\n", totalPaths);
}
// Function to calculate the total number of paths
int calculatePaths(int column, int row) {
    // Base case: if either column or row is 0, there's only one path
    if (column == 0 || row == 0) {
        return 1;
    }
    return calculatePaths(column - 1, row) + calculatePaths(column, row - 1);
}
// Functions for Task 2: The Human Pyramid
void task2HumanPyramid() {
    int levels = 5;
    float weights[15]; // Array to store weight of all cheerleaders (for 5 levels)
    printf("Please enter the weights of the cheerleaders:\n");

    // Input weights for all cheerleaders
    for (int i = 0; i < 15; i++) {
        scanf("%f", &weights[i]);
        // Validate input for negative weights
        if (weights[i] < 0) {
            printf("Negative weights are not supported.\n");
            return;
        }
    }
    printf("\nThe total weight on each cheerleader is:\n");
    // Display weights in a pyramid format
    for (int row = 0, index = 0; row < levels; row++) {
        for (int column = 0; column <= row; column++, index++) {
            float totalWeight = calculateWeight(row, column, weights);
            printf("%.2f ", totalWeight);
        }
        printf("\n");
    }
}
// Recursive function to calculate the weight supported by a cheerleader
float calculateWeight(int row, int column, float weights[]) {
    // Calculate the index of cheerleader in the array
    int index = (row * (row + 1)) / 2 + column;
    
    // Base case: if at the top of the pyramid, return their own weight
    if (row == 0) {
        return weights[index];
    }

    // Recursive case: calculate the weight supported from above
    float leftWeight = (column > 0) ? calculateWeight(row - 1, column - 1, weights) / 2 : 0;
    float rightWeight = (column < row) ? calculateWeight(row - 1, column, weights) / 2 : 0;
    return weights[index] + leftWeight + rightWeight;
}
// Main Function for Task 3
void task3ParenthesisValidator() {
    char input[MAX_INPUT_SIZE];
    printf("Please enter a term for validation:\n");
    scanf("%99s", input);
    // Call recursive validator
    if (validateRecursive(input)) {
        printf("The parentheses are balanced correctly.\n");
    }
    else {
        printf("The parentheses are not balanced correctly.\n");
    }
}
// Recursive function to validate parentheses
int validateRecursiveHelper(char input[], int index, char stack[], int top) {
    if (input[index] == '\0') {
        return top == -1;
    }
    char ch = input[index];
    // Push opening brackets to the stack
    if (ch == '(' || ch == '[' || ch == '{' || ch == '<') {
        if (top >= STACK_SIZE - 1) return 0;
        stack[++top] = ch;
    } else if (ch == ')' || ch == ']' || ch == '}' || ch == '>') {
        if (top == -1) return 0;
        char open = stack[top--];
        if (!isMatch(open, ch)) return 0;
    }
    return validateRecursiveHelper(input, index + 1, stack, top);
}
int validateRecursive(char input[]) {
    char stack[STACK_SIZE];
    return validateRecursiveHelper(input, 0, stack, -1);
}
// Check if opening and closing parentheses match
int isMatch(char open, char close) {
    return (open == '(' && close == ')') ||
        (open == '[' && close == ']') ||
        (open == '{' && close == '}') ||
        (open == '<' && close == '>');
}
// Main function: task4QueensBattle
void task4QueensBattle() {
    char board[MAX][MAX];
    int cols[MAX] = {0};
    int areas[MAX_AREAS] = {0};
    int boardSize;

    printf("Please enter the board dimensions:\n");
    scanf("%d", &boardSize);
    while ((getchar()) != '\n'); // clear newline

    printf("Please enter a %d*%d puzzle board:\n", boardSize, boardSize);
    for (int i = 0; i < boardSize; i++) {
        scanf("%s", board[i]);
    }

    if (solveQueens(0, board, boardSize, cols, areas)) {
        printf("Solution:\n");
        printSolution(board, boardSize);
    } else {
        printf("This puzzle cannot be solved.\n");
    }
}

// Check if placing a queen at (row, col) is safe from adjacent queens
int isSafe(int row, int col, char board[MAX][MAX], int boardSize) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int ni = row + i;
            int nj = col + j;
            if (ni >= 0 && ni < boardSize && nj >= 0 && nj < boardSize) {
                if (board[ni][nj] == 'X') return 0;
            }
        }
    }
    return 1;
}

// Recursive solver
int solveQueens(int row, char board[MAX][MAX], int boardSize, int cols[MAX], int areas[MAX_AREAS]) {
    if (row == boardSize) return 1;

    for (int col = 0; col < boardSize; col++) {
        char area = board[row][col];
        unsigned char code = (unsigned char)area;

        if (cols[col] || areas[code]) continue;
        if (!isSafe(row, col, board, boardSize)) continue;

        board[row][col] = 'X';
        cols[col] = 1;
        areas[code] = 1;

        if (solveQueens(row + 1, board, boardSize, cols, areas)) return 1;

        board[row][col] = area;
        cols[col] = 0;
        areas[code] = 0;
    }
    return 0;
}

// Output the board
void printSolution(char board[MAX][MAX], int boardSize) {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == 'X') printf("X ");
            else printf("* ");
        }
        printf("\n");
    }
}
