// Written by Lex | Tuesday 23 august 2022, 01:17:04 AM

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int winCheck(int board[3][3]) {

	// Check for straight lines | Horizontal & Vertical

	for (int i = 0; i < 3; i++) {
		if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != -1) {
			return board[i][0];
		}
	}

	for (int i = 0; i < 3; i++) {
		if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != -1) {
				return board[0][i];
		}
	}


	// Check for / or \ pattern

	if (board[2][0] == board[1][1] && board[2][0] == board[0][2] && board[2][0] != -1) {
		return board[2][0];
	}

	if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != -1) {
		return board[0][0];
	}


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
		return 2;
	}

	return 3;

	// Return codes :

	// 0 - Line for O
	// 1 - Line for X
	// 2 - Board full
	// 3 - Nothing

}

char returnDisplay(int value) {

	// Return visible characters based on board values.

	switch (value) {
		case -1:
			return '-';
		case 0: 
			return 'O';
		case 1:
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

int verifyWin(int board[3][3]) {

	int win = winCheck(board);
	
	switch (win) {
		case 0:
			system("@cls||clear");
			drawboard(board);
			printf("\n--> Game Ended, you won!\n");
			break;
		case 1:
			system("@cls||clear");
			drawboard(board);
			printf("\n--> Game Ended, you lost\n");
			break;
		case 2:
			system("@cls||clear");
			drawboard(board);
			printf("\n--> Game Ended, nobody won lmao!\n");
			break;
		case 3:
			break;
		default:
			system("@cls||clear");
			drawboard(board);
			printf("\n--> Game Ended, nobody won lmao!\n");
			break;
	}

	return win;

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

	// Place initial X somewhere on the board

	AIPlace(board, 'r');

	// Keep player in game loop as long as the game is not finished

	while (game) {

		// Draw board and get decision from player

		drawboard(board);
		getDec(board);

		// Check if there are any winning moves after player decision

		if (verifyWin(board) != 3) {
			game = false;
			break;
		}

		if(AIPlace(board, 'r') && game) {

			// Check if there are any winning moves after A.I decision

			if (verifyWin(board) != 3) {
				game = false;
				break;
			}

		}
	}
}
