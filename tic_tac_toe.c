#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

// Node for the stack
typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

// Stack Implementation
typedef struct {
    StackNode* top;
} Stack;

// Queue Node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Queue Implementation
typedef struct {
    Node* front;
    Node* rear;
} Queue;

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

int isEmpty(Queue* queue) {
    return (queue->front == NULL);
}

void enqueue(Queue* queue, int item) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = item;
    newNode->next = NULL;

    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

int dequeue(Queue* queue) {
    if (isEmpty(queue))
        return -1;

    Node* temp = queue->front;
    int item = temp->data;

    queue->front = temp->next;
    free(temp);

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    return item;
}

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

int isStackEmpty(Stack* stack) {
    return (stack->top == NULL);
}

void push(Stack* stack, int item) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = item;
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(Stack* stack) {
    if (isStackEmpty(stack))
        return -1;

    StackNode* temp = stack->top;
    int item = temp->data;

    stack->top = temp->next;
    free(temp);

    return item;
}

// Function to display the Tic Tac Toe board with borders
void displayBoard(char board[SIZE][SIZE]) {
    printf("+---+---+---+\n");
    for (int i = 0; i < SIZE; i++) {
        printf("| ");
        for (int j = 0; j < SIZE; j++) {
            printf("%c | ", board[i][j]);
        }
        printf("\n+---+---+---+\n");
    }
    printf("\n");
}

// Function to display the rules
void displayRules() {
    printf("*************  Welcome to Tic Tac Toe!  *************\n");
    printf("\t\t\t\t\t\tRULES OF THE GAME:\n");
    printf("1. Players take turns to input a number corresponding to the cell they want to mark.\n");
    printf("2. The board is a 3x3 grid with each cell labeled with a unique number.\n");
    printf("3. The first player to mark three consecutive cells either horizontally, vertically, or diagonally wins.\n");
    printf("4. If all cells are filled and no player has won, the game is a draw.\n");
    printf("5. You can undo your last move using the 'u' command.\n\n");
    printf("\n\n\n\t\t\t\t\tLETS PLAY!!!!\n\n");
}

// Function to check for a win
int checkWin(char board[SIZE][SIZE], char symbol) {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) {
            return 1;
        }
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) {
            return 1;
        }
    }

    // Check diagonals
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) {
        return 1;
    }
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) {
        return 1;
    }

    return 0;
}

// Function to play the game
void playGame() {
    char board[SIZE][SIZE];
    Queue* moves = createQueue();
    Stack* moveHistory = createStack();

    // Initialize the board with unique numbers
    int cellNumber = 1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '0' + cellNumber++;
        }
    }

    displayRules();

    // Display initial board
    displayBoard(board);

    int cellChoice;
    char currentPlayer = 'X';
    int totalMoves = 0;

    while (totalMoves < SIZE * SIZE) {
        printf("Player %c's turn. Enter cell number (or 'u' to undo): ", currentPlayer);

        char input[2];
        scanf("%s", input);

        if (input[0] == 'u') {
            if (!isStackEmpty(moveHistory)) {
                // Undo move
                int lastMove = pop(moveHistory);
                int row = (lastMove - 1) / SIZE;
                int col = (lastMove - 1) % SIZE;
                board[row][col] = '0' + lastMove;
                totalMoves--;
                displayBoard(board);
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                continue;
            } else {
                printf("Cannot undo. No moves to undo.\n");
                continue;
            }
        }

        sscanf(input, "%d", &cellChoice);

        // Convert cell number to row and column
        int row = (cellChoice - 1) / SIZE;
        int col = (cellChoice - 1) % SIZE;

        if (cellChoice < 1 || cellChoice > SIZE * SIZE || board[row][col] == 'X' || board[row][col] == 'O') {
            printf("Invalid move. Try again.\n");
            continue;
        }

        board[row][col] = currentPlayer;
        totalMoves++;
        enqueue(moves, cellChoice);
        push(moveHistory, cellChoice);
        displayBoard(board);

        if (checkWin(board, currentPlayer)) {
            printf("Player %c wins!\n", currentPlayer);
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    if (totalMoves == SIZE * SIZE) {
        printf("It's a draw!\n");
    }

    // Free the linked list nodes
    while (!isEmpty(moves)) {
        dequeue(moves);
    }

    free(moves);

    // Free the stack nodes
    while (!isStackEmpty(moveHistory)) {
        pop(moveHistory);
    }

    free(moveHistory);
}

// Main function
int main() {
    printf("Tic Tac Toe Game using Queue, Linked List, and Stack\n");
    playGame();
    return 0;
}
