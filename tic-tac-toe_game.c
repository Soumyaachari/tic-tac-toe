#include <stdio.h>
#include <stdlib.h>

// Define a structure for the player
struct Player 
{
    char symbol;
    int score;
};

// Function to initialize the game grid
char** initializeGrid() 
{
    char** grid = (char**)malloc(3 * sizeof(char*));
    for (int i = 0; i < 3; i++) 
	{
        grid[i] = (char*)malloc(3 * sizeof(char));
        for (int j = 0; j < 3; j++) 
		{
            grid[i][j] = ' ';
        }
    }
    return grid;
}

// Function to print the current state of the grid
void printGrid(char** grid) 
{
    for (int i = 0; i < 3; i++) 
	{
        for (int j = 0; j < 3; j++) 
		{
            printf("%c", grid[i][j]);
            if (j < 2) printf("  | ");
        }
        printf("\n");
        if (i < 2) printf("-------------\n");
    }
}

// Function to check if a player has won
int checkWin(char** grid, char symbol) 
{
    // Check rows and columns
    for (int i = 0; i < 3; i++) 
	{
        if (grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol) 
		return 1; // Check rows
        if (grid[0][i] == symbol && grid[1][i] == symbol && grid[2][i] == symbol) 
		return 1; // Check columns
    }

    // Check diagonals
    if (grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol) 
	return 1; // Check diagonal 

    return 0; // No win
}
  
int main() 
{
    struct Player playerX = {'X',0};
    struct Player playerO = {'O',0};

    char** grid = initializeGrid();
    int currentPlayer = 0; // 0 for player X, 1 for player O
    int moves = 0;

    printf("Tic Tac Toe Game\n");

    while (1) {
        printf("\nCurrent Grid:\n");
        printGrid(grid);

        int row, col;
        printf("Player %c, enter your move (row (0-2) & column(0-2)): ", (currentPlayer == 0) ? playerX.symbol : playerO.symbol);
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= 3 || col < 0 || col >= 3 || grid[row][col] != ' ') 
		{
            printf("Invalid move. Try again.\n");
            continue;
        }

        grid[row][col] = (currentPlayer == 0) ? playerX.symbol : playerO.symbol;
        moves++;

        if (checkWin(grid, (currentPlayer == 0) ? playerX.symbol : playerO.symbol)) 
		{
            printf("\nPlayer %c wins!!\n", (currentPlayer == 0) ? playerX.symbol : playerO.symbol);
            (currentPlayer == 0) ? playerX.score++ : playerO.score++;
            printf("Scores: Player X - %d, Player O - %d\n", playerX.score, playerO.score);
			break;
        } else if (moves == 9) {
            printf("\nIt's a draw!\n");
            break;
        }

        currentPlayer = 1 - currentPlayer; // Switch player
    }

    // Free dynamically allocated memory
    for (int i = 0; i < 3; i++) 
	{
        free(grid[i]);
    }
    free(grid);

    return 0;
}

