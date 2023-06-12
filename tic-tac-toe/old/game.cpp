#include <iostream>
#include "game.h"

using namespace std;

// flow of the game:
// - select board size, also number in a row required to win
// - input moves until someone wins
// - new game or quit

void getBoardSize(int& x, int& y)
{
	cout << "Enter board width: ";
	cin >> x;
	cout << "Enter board height: ";
	cin >> y;

	cout << x << ", " << y << endl;
}

void centerBoard(int x, int y)
{
	// account for where center will be based on the board size
	// draw lines
	int breadth = x + x + 1;
	int depth = y + y + 1;	
}

void Game::newGame(int boardWidth, int boardHeight)
{
	board.clear();
	board = vector<vector<Position>>(boardWidth, vector<Position>(boardHeight, Position::blank));
}

void Game::inputMove(int x, int y)
{
	board[x][y] = playerToggle;
	togglePlayer();
}

bool checkForWin()
{
	// horizontal
	// vertical
	// diagonal
	return false;
}

void Game::togglePlayer()
{
	if (playerToggle == Position::x)
		playerToggle = Position::o;
	else
		playerToggle = Position::x;
}
