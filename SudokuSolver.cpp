//This program generates "Sudoku Puzzle" and takes input from user to solve the puzzle 

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>

// ANSI Escape Codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

#define GRID_SIZE 9
#define SUBGRID_SIZE 3
#define EMPTY_SPACE 0
int emptyCell_counter = 0;

// Check row, column and 3x3 grid if puzzle is valid
bool isValid(int grid[GRID_SIZE][GRID_SIZE], int row, int col, int num) {
	for (int i = 0; i < GRID_SIZE; i++)
	{
		if (grid[row][i] == num || grid[i][col] == num ||
			grid[row - row % SUBGRID_SIZE + i / SUBGRID_SIZE][col - col % SUBGRID_SIZE + i % SUBGRID_SIZE] == num) 
		{
			return false;			
		}
	}
	return true; 
}

// Solve the puzzle 
bool solveSudoku(int grid[GRID_SIZE][GRID_SIZE]) {
	for (int row = 0; row < GRID_SIZE; row++) {	
		for (int col = 0; col < GRID_SIZE; col++) {

			if (grid[row][col] == EMPTY_SPACE) // if cell is empty
			{
				for (int num = 1; num <= 9; num++) {
					if (isValid(grid, row, col, num)) // if grid[row][col] is valid with num variable, grid[row][col] equal to num.
					{
						grid[row][col] = num;
						if (solveSudoku(grid)) {
							return true;
						}
						grid[row][col] = EMPTY_SPACE;
					}
				}
				return false;
			}
		}
	}
	return true;
}

// Generating the puzzle
void generateSudokuPuzzle(int grid[GRID_SIZE][GRID_SIZE], int numClues) {

	std::srand(std::time(0));
	solveSudoku(grid);

	std::vector<std::pair<int, int>> cells;		// makes a grid that named as cells

	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			cells.emplace_back(i, j);		// generate a 9x9 grid
		}
	}

	//Shuffle
	std::random_shuffle(cells.begin(), cells.end());

	for (int i = 0; i < numClues; i++)
	{
		int row = cells[i].first;	// first stored value at row
		int col = cells[i].second;	// second stored value at column
		int temp = grid[row][col];
		grid[row][col] = EMPTY_SPACE;
	}
}

//printing the puzzle
void printGrid(int grid[GRID_SIZE][GRID_SIZE]) {
	std::cout << std::endl;

	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (grid[i][j] == EMPTY_SPACE) {
				std::cout << BLUE << "." << "  ";
			}
			else {
				std::cout << RESET << grid[i][j] << "  ";
			}
		}
		std::cout << std::endl;
	}
	emptyCell_counter++;
	std::cout << std::endl;
}

int main() {
	int sudoku[GRID_SIZE][GRID_SIZE] = { 0 };	// empty array
	int row = 0;
	int col = 0;
	int guess = 0;
	int clue = 0;
	int level = 0;

	std::cout << "Select the level of puzzle!" << std::endl;
	std::cout << "Type (1) for EASY" << std::endl;
	std::cout << "Type (2) for MIDDLE" << std::endl;
	std::cout << "Type (3) for HARD" << std::endl;
	std::cout << "Choice: ";
	std::cin >> level;
	std::cout << std::endl;

	switch (level) {
	case 1:
		clue = 20;
		break;
	case 2:
		clue = 40;
		break;
	case 3:
		clue = 50;
		break;
	}
	

	//Generate sudoku with how many clues you want
	generateSudokuPuzzle(sudoku, clue);

	//print sudoku
	std::cout << "Generated Sudoku Puzzle:" << std::endl;
	printGrid(sudoku);
	emptyCell_counter--;

		
	while (clue - emptyCell_counter != 0) {
		std::cout << YELLOW << "Enter row (1-9): ";
		std::cin >> row;
		row--;

		std::cout << YELLOW << "Enter column (1-9): ";
		std::cin >> col;
		col--;

		if (sudoku[row][col] == EMPTY_SPACE) {
			std::cout << GREEN << "Enter guess (1-9): ";
			std::cin >> guess;

			if (guess >= 1 && guess <= 9) {
				if (isValid(sudoku, row, col, guess)) {
					sudoku[row][col] = guess;
				}
				else {
					std::cout << RED << "Invalid guess! Try again." << std::endl << std::endl;
				}
			}
			else {
				std::cout << RED << "Invalid guess! Guess must be between 1 and 9." << std::endl << std::endl;
			}
			std::cout << std::endl;
			std::cout << GREEN << "Correct! Updated Sudoku:" << std::endl << std::endl;
			printGrid(sudoku);
		}
		else {
			std::cout << BLUE << "This cell is already filled! Choose another cell." << std::endl << std::endl;
		}
	}

	if (clue - emptyCell_counter == 0) {
		std::cout << GREEN << "You've sucessfuly finished the sudoku puzzle. Congratulations!" << std::endl;
	}
	return 0;
}