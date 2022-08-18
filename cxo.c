#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

char returnDisplay(int value) {

	// Return visible characters based on board values.

	if (value == -1) {
		return '-';
	}
	if (value == 0) {
		return 'O';
	}
	if (value == 1) {
		return 'X';
	}


	// For unknown value return empty space

	return ' ';

}

void drawboard( int board[3][3] ) {

	// Clear screen and draw new board

	system("@cls||clear");

	// Top border

		for (int i = 0; i <= 12; i++) {
			printf("#");
		}
		printf("\n");

	// Middle lines

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				printf("# %c ", returnDisplay(board[i][j]));
			}
			printf("#\n");
		}

	// Bottom border

		for (int i = 0; i <= 12; i++) {
			printf("#");
		}
		printf("\n");
}

int place(int board[3][3], int x, int y) {

	// Check if space is empty and return | 0 - OK | 1 - NOT OK
	// y & x have switched positions to make it easier for player to know what is going on

	if (board[y][x] == -1) {
		board[y][x] = 0;
		return 0;
	}
	else {
		return 1;
	}

}

void invalidMove(int board[3][3]) {

	// Clear the screen and re-draw the board after an invalid move
	system("@cls||clear");
	drawboard(board);
	printf("\nInvalid move! Try again.\n");

}

void getDec(int board[3][3]) {
	// Get decision from player and push to board

	int x, y;
	printf("\nWhat's your next move? (X axis) => ");
	scanf("%d", &x);
	printf("What's your next move? (Y axis) => ");
	scanf("%d", &y);

	// Check if move is valid

	if (x >= 0 && x <= 3 && y >= 0 && y <=3) {
		// If there isn't an empty space at the desired place give out an invalid move error and ask again for new coords
		if(place(board, x - 1, y - 1)) {
			invalidMove(board);
			getDec(board);
		}
	}
	else {
		invalidMove(board);
		getDec(board);
	}
}

int AIPlace(int board[3][3], char mode) {

	// Check if there is any space left.

	bool space = false;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == -1) {
				space = true;
			}
		}
	}
	if (space == false) {
		// Return failure to find free space
		return 0;
	}

	// Random mode

	if (mode == 'r') {
		int genX = rand() % 4;
		int genY = rand() % 4;
		while (board[genX][genY] != -1) {
			genX = rand() % 4;
			genY = rand() % 4;
		}
		board[genX][genY] = 1;
	}

	// Return successful placement
	return 1;

}


int main() {

	// Generate board and game state

	bool game = true;
	int board[3][3];
	srand(time(NULL));

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j] = -1;
		}
	}

	// Keep player in game loop as long as the game is not finished

	while (game) {

		// Check if there are any valid moves for A.I and if there are draw new board & get Dec from user.

		if(AIPlace(board, 'r')) {
			drawboard(board);
			getDec(board);
		}
		else {

			// Game ends, display end screen and quit loop

			system("@cls||clear");
			printf("Game Ended, nobody won lmao\n");
			break;
		}
	}
}


// TO DO:
// + Check if board is full
// + Check for winning combo
