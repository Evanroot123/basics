#include <iostream>
#include "game.h"

using namespace std;

// flow of the game:
// - select board size, also number in a row required to win
// - input moves until someone wins
// - new game or quit

void Game::newGame(int boardWidth, int boardHeight, int moves)
{
	board.clear();
	width = boardWidth;
	height = boardHeight;
	numMoves = 0;
	movesToWin = moves;
	gameResultStatus = Result::None;
	playerToggle = Position::x;
	board = vector<vector<Position>>(boardHeight, vector<Position>(boardWidth, Position::blank));
}

void Game::inputMove(int col, int row)
{
	if (board[row][col] == Position::blank)
	{
		board[row][col] = playerToggle;
		togglePlayer();
		numMoves++;
		checkForWinOrCats();
	}
}

void Game::checkForWinOrCats()
{
	// horizontal
	if (checkHorizontal(Position::x))
		gameResultStatus = Result::X_WINS;
	else if (checkHorizontal(Position::o))
		gameResultStatus = Result::O_WINS;
	// vertical
	if (checkVertical(Position::x))
		gameResultStatus = Result::X_WINS;
	else if (checkHorizontal(Position::o))
		gameResultStatus = Result::O_WINS;
	// diagonal
	if (checkDiagonal(Position::x))
		gameResultStatus = Result::X_WINS;
	else if (checkDiagonal(Position::o))
		gameResultStatus = Result::O_WINS;
	// cats - check last
	int totalPossibleMoves = width * height;
	if (numMoves >= totalPossibleMoves)
		gameResultStatus = Result::Cats;
}

bool Game::checkVertical(Position pos)
{
	int count = 0;

	for (int col = 0; col < width; col++)
	{
		count = 0;
		for (int row = 0; row < height; row++)
		{
			if (board[row][col] == pos)
				count++;
			else
				count = 0;
			
			if (count >= movesToWin)
				return true;

			int temp = height - row;
			if (count + temp <= movesToWin)
				break;
		}
	}

	return false;
}

bool Game::checkHorizontal(Position pos)
{
	int count = 0;

	for (int row = 0; row < height; row++)
	{
		count = 0;
		for (int col = 0; col < width; col++)
		{
			if (board[row][col] == pos)
				count++;
			else
				count = 0;
			
			if (count >= movesToWin)
				return true;

			int temp = width - col;
			if (count + temp <= movesToWin)
				break;
		}
	}

	return false;
}

bool Game::checkDiagonal(Position pos)
{
	int count = 0;
	
	// top half forward - including middle
	for (int col = 0; col < width; col++)
	{
		for (int x = col, y = 0; x < width && y < height; x++, y++)
		{
			if (board[y][x] == pos)
				count++;
			else
				count = 0;

			int temp1 = width - x;
			int temp2 = height - y;

			if (count >= movesToWin)
				return true;
			if (count + temp1 <= movesToWin)
				break;
			if (count + temp2 <= movesToWin)
				break;
		}
	}

	count = 0;
	// bottom half forward - discluding middle
	for (int row = 1; row < height; row++)
	{
		for (int x = 0, y = row; x < width && y < height; x++, y++)
		{
			if (board[y][x] == pos)
				count++;
			else
				count = 0;

			int temp1 = width - x;
			int temp2 = height - y;

			if (count >= movesToWin)
				return true;
			if (count + temp1 <= movesToWin)
				break;
			if (count + temp2 <= movesToWin)
				break;

		}
	}

	count = 0;
	// top half backward - including middle
	for (int col = width - 1; col > -1; col--)
	{
		for (int x = col, y = 0; x > -1 && y < height; x--, y++)
		{
			if (board[y][x] == pos)
				count++;
			else
				count = 0;

			int temp = height - y;

			if (count >= movesToWin)
				return true;
			if (count + x < movesToWin)
				break;
			if (count + temp <= movesToWin)
				break;
		}
	}

	count = 0;
	// bottom half backward - discluding middle
	for (int row = 1; row < height; row++)
	{
		for (int x = width - 1, y = row; x > -1 && y < height; x--, y++)
		{
			if (board[y][x] == pos)
				count++;
			else
				count = 0;

			int temp = height - y;

			if (count >= movesToWin)
				return true;
			if (count + x < movesToWin)
				break;
			if (count + temp <= movesToWin)
				break;
		}
	}

	return false;
}

void Game::togglePlayer()
{
	if (playerToggle == Position::x)
		playerToggle = Position::o;
	else
		playerToggle = Position::x;
}
