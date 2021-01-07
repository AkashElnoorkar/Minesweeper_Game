#include<bits/stdc++.h>

using namespace std;

#define BEGINNER 0
#define INTERMEDIATE 1
#define ADVANCED 2
#define MAXSIDE 25
#define MAXMINES 99
#define MOVESIZE 256 // (25*25-99)

int SIDE; // Side lenght of the board.
int MINES;// Number of mines on the board.

bool isValid(int row, int col) // A utility function to check whether the given cell is valid or not.
{
	// Returns true if row number and column number are in range.
	return (row >= 0) && (row < SIDE) && (col >= 0) && (col < SIDE);
}

bool isMine(int row, int col, char board[][MAXSIDE]) // A utility function to check whether the given cell (row,col) has a mine or not.
{
	if (board[row][col] == '*')
		return (true);
	else
		return(false);
}

void makeMove(int* x, int* y) // A function to get user's move.
{
	// Take the input move.
	printf("Enter your move, (row, column) -> ");
	scanf("%d%d", x, y);
	return;
}

void printBoard(char myBoard[][MAXSIDE]) // A function to print the current gameplay board.
{
	int i, j;
	printf("    ");
	for (i = 0; i < SIDE; i++)
		printf("%d", i);
	printf("\n\n");
	for (i = 0; i < SIDE; i++)
	{
		printf("%d    ", i);
		for (j = 0; j < SIDE; j++)
			printf("%c", myBoard[i][j]);
		printf("\n");
	}
	return;
}

int countAdjacentMines(int row, int col, int mines[][2], char realBoard[][MAXSIDE]) // A function to count the number of mines in the adjacent cells.
{
	int count = 0;
	// Only processes the cells if they are valid.
	if (isValid(row - 1, col) == true) 
	{
		if (isMine(row - 1, col, realBoard) == true)
			count++;
	}
	if (isValid(row + 1, col) == true)
	{
		if (isMine(row + 1, col, realBoard) == true)
			count++;
	}
	if (isValid(row, col + 1) == true)
	{
		if (isMine(row, col + 1, realBoard) == true)
			count++;
	}
	if (isValid(row, col - 1) == true)
	{
		if (isMine(row, col - 1, realBoard) == true)
			count++;
	}
	if (isValid(row - 1, col + 1) == true)
	{
		if (isMine(row - 1, col + 1, realBoard) == true)
			count++;
	}
	if (isValid(row - 1, col - 1) == true)
	{
		if (isMine(row - 1, col - 1, realBoard) == true)
			count++;
	}
	if (isValid(row + 1, col + 1) == true)
	{
		if (isMine(row + 1, col + 1, realBoard) == true)
			count++;
	}
	if (isValid(row + 1, col - 1) == true)
	{
		if (isMine(row + 1, col - 1, realBoard) == true)
			count++;
	}
	return (count);
}

bool playMinesweeperUtil(char myBoard[][MAXSIDE], char realBoard[][MAXSIDE], int mines[][2], int row, int col, int* movesLeft) // A recursive function to play the minesweeper game.
{
	// Base case of recursion.
	if (myBoard[row][col] != '-')
		return (false);
	int i;
	// You opened a mine, you are going to lose.
	if (realBoard[row][col] == '*')
	{
		myBoard[row][col] = '*';
		for (i = 0; i < MINES; i++)
			myBoard[mines[i][0]][mines[i][1]] = '*';
		printBoard(myBoard);
		printf("\nYOU LOST!\n");
		return (true);
	}
	else
	{
		// Calculate the number of adjacent mines and put it on the board.
		int count = countAdjacentMines(row, col, mines, realBoard);
		(*movesLeft)--;
		myBoard[row][col] = count + '0';
		if (!count)
		{
			if (isValid(row - 1, col) == true)
			{
				if (isMine(row - 1, col, realBoard) == true)
					playMinesweeperUtil(myBoard, realBoard, mines, row - 1, col, movesLeft);
			}
			if (isValid(row + 1, col) == true)
			{
				if (isMine(row + 1, col, realBoard) == true)
					playMinesweeperUtil(myBoard, realBoard, mines, row + 1, col, movesLeft);
			}
			if (isValid(row, col + 1) == true)
			{
				if (isMine(row, col + 1, realBoard) == true)
					playMinesweeperUtil(myBoard, realBoard, mines, row, col + 1, movesLeft);
			}
			if (isValid(row, col - 1) == true)
			{
				if (isMine(row, col - 1, realBoard) == true)
					playMinesweeperUtil(myBoard, realBoard, mines, row, col - 1, movesLeft);
			}
			if (isValid(row - 1, col + 1) == true)
			{
				if (isMine(row - 1, col + 1, realBoard) == true)
					playMinesweeperUtil(myBoard, realBoard, mines, row - 1, col + 1, movesLeft);
			}
			if (isValid(row - 1, col - 1) == true)
			{
				if (isMine(row - 1, col - 1, realBoard) == true)
					playMinesweeperUtil(myBoard, realBoard, mines, row - 1, col - 1, movesLeft);
			}
			if (isValid(row + 1, col + 1) == true)
			{
				if (isMine(row + 1, col + 1, realBoard) == true)
					playMinesweeperUtil(myBoard, realBoard, mines, row + 1, col + 1, movesLeft);
			}
			if (isValid(row + 1, col - 1) == true)
			{
				if (isMine(row + 1, col - 1, realBoard) == true)
					playMinesweeperUtil(myBoard, realBoard, mines, row + 1, col - 1, movesLeft);
			}
		}
		return false;
	}
}

void placeMines(int mines[][2], char realBoard[][MAXSIDE]) // A function to place the mines randomly on the board.
{
	bool mark[MAXSIDE * MAXSIDE];
	memset (mark, false, sizeof(mark));
	// Continue until all random mines have been created.
	for (int i = 0; i < MINES;)
	{
		int random = rand() % (SIDE * SIDE);
		int x = random / SIDE;
		int y = random % SIDE;
		// Add the mine if no mins is placed at this postion on the board.
		if (mark[random] == false)
		{
			// Row index of the mine.
			mines[i][0] = x;
			// Column index of the mine.
			mines[i][1] = y;
			// Place the mine.
			realBoard[mines[i][0]][mines[i][1]] = '*';
			mark[random] = true;
			i++;
		}
	}
	return;
}

void initialise(char realBoard[][MAXSIDE], char myBoard[][MAXSIDE]) // A function to initialise the game.
{
	// Initialise the random number generator, so that the same configuration doesn't appear.
	srand(time (NULL));
	// Assign all the cells as mine-free.
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			myBoard[i][j] = realBoard[i][j] = '-';
		}
	}
	return;
}

void cheatMinesweeper(char realBoard[][MAXSIDE]) // A function to cheat by revealing where all the mines are placed.
{
	printf("The mine's locations are : \n");
	printBoard(realBoard);
	return;
}

void replaceMine(int row, int col, char board[][MAXSIDE]) // A funtion to replace the mine from (row,col) and put it to a vacant space.
{
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			// Find the first location in the board which is not having a mine and put a mine there.
			if (board[i][j] != '*')
			{
				board[i][j] = '*';
				board[row][col] = '-';
				return;
			}
		}
	}
	return;
}

void playMinesweeper() // A function to play Minesweeper game.
{
	bool gameOver = false; // Initially the game is not over.
	char realBoard[MAXSIDE][MAXSIDE], myBoard[MAXSIDE][MAXSIDE]; // Actual board and my board.
	int movesLeft = SIDE * SIDE - MINES, x, y;
	int mines[MAXMINES][2]; // Stores (x,y) coordinates of all mines.
	initialise(realBoard, myBoard);
	placeMines(mines, realBoard); // Place the mines randomly.
	// You are in the game until you have not opened a mine. So, keep playing.
	int currentMoveIndex = 0;
	while (gameOver == false)
	{
		printf("Current status of the board : \n");
		printBoard(myBoard);
		makeMove(&x, &y);
		// This is to guarantee that the first move is always safe. If, it is the first move of the game.
		if (currentMoveIndex == 0)
		{
			// If the first move itself is a mine, then we remove the mine from that location.
			if (isMine(x, y, realBoard) == true)
				replaceMine(x, y, realBoard);
		}
		currentMoveIndex++;
		gameOver = playMinesweeperUtil(myBoard, realBoard, mines, x, y, &movesLeft);
		if ((gameOver == false) && (movesLeft == 0))
		{
			printf("\nYOU WON!\n");
			gameOver = true;
		}
	}
	return;
}

void chooseDifficultyLevel() // A function to choose the difficulty level of the game.
{
	/*
	--> BEGINNER = 9 * 9 Cells and 10 Mines.
	--> INTERMEDIATE = 16 * 16 Cells and 40 Mines.
	--> ADVANCED = 24 * 24 Cells and 99 Mines.
	*/
	int level;
	printf("Enter the Difficulty Level : \n");
	printf("Press '0' for BEGINNER (9 * 9 Cells and 10 Mines) : \n");
	printf("Press '1' for INTERMEDIATE (16 * 16 Cells and 40 Mines) : \n");
	printf("Press '2' for ADVANCED (24 * 24 Cells and 99 Mines) : \n");
	cin>>level;
	if (level == BEGINNER)
	{
		SIDE = 9;
		MINES = 10;
	}
	if (level == INTERMEDIATE)
	{
		SIDE = 16;
		MINES = 40;
	}
	if (level == ADVANCED)
	{
		SIDE = 24;
		MINES = 99;
	}
	return;
}

int main() // Driver program to test the above functions.
{
	chooseDifficultyLevel();
	playMinesweeper();
	return (0);
}
