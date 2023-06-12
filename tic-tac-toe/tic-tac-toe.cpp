#include <iostream>
#include <system_error>
#include <windows.h>
#include "game.h"

using namespace std;

#define WIDTH	150
#define HEIGHT	50

void checkGameForConclusion(Game& game);
void getMovesToWin(int& moves);
void getBoardSize(int& x, int& y);
void clearScreen(string& screenWindow);
void printConclusionString(string& message);
void setConsoleScreenBuffer(SHORT x, SHORT y);
void outputInfo(CONSOLE_SCREEN_BUFFER_INFO& info);
void processUserInput(HANDLE input, HANDLE output, Game& game, string& screenWindow);
void updateCursorPosition(int x, int y, HANDLE output, Game& game);
void drawBoard(HANDLE output, Game& game, string& consoleWindow);
char positionToChar(Position pos);

SHORT startingCursorX = 0;
SHORT startingCursorY = 0;
int cursorX = 0, cursorY = 0;
bool quitZeGame = false;
bool gameConcluded = false;

int main()
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE inputHandle = GetStdHandle(STD_INPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(outputHandle, &info);

	string screenWindow(info.dwSize.X * info.dwSize.Y, ' ');

	int boardWidth = 3, boardHeight = 3;
	getBoardSize(boardWidth, boardHeight);
	int moves = 3;
	getMovesToWin(moves);

	Game game;
	game.newGame(boardWidth, boardHeight, moves);
	drawBoard(outputHandle, game, screenWindow);
	updateCursorPosition(0, 0, outputHandle, game);
	while (!quitZeGame)
	{
		if (!gameConcluded)
		{
			drawBoard(outputHandle, game, screenWindow);
			checkGameForConclusion(game);
		}
		processUserInput(inputHandle, outputHandle, game, screenWindow);

	}
	clearScreen(screenWindow);
}

void checkGameForConclusion(Game& game)
{
	string message = "";
	switch(game.gameResultStatus)
	{
		case Result::Cats:
			gameConcluded = true;
			message = "Cats Game!";
			printConclusionString(message);
			break;
		case Result::X_WINS:
			gameConcluded = true;
			message = "X Wins!";
			printConclusionString(message);
			break;
		case Result::O_WINS:
			gameConcluded = true;
			message = "O Wins!";
			printConclusionString(message);
			break;
	}
}

void getBoardSize(int& x, int& y)
{
	cout << "Enter board width: " << endl;
	cin >> x;
	cout << "Enter board height: " << endl;
	cin >> y;
}

void getMovesToWin(int& moves)
{
	cout << "Enter moves to win: " << endl;
	cin >> moves;
}

void clearScreen(string& screenWindow)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(output, &info);
	DWORD written;
	FillConsoleOutputCharacter(output, ' ', info.dwSize.X * info.dwSize.Y, {0,0}, &written);
	SetConsoleCursorPosition(output, {0,0});
	screenWindow.clear();
	screenWindow.append(info.dwSize.X * info.dwSize.Y, ' ');
}

void printConclusionString(string& message)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(output, &info);
	DWORD written;
	SHORT centerX = info.dwSize.X / 2;
	SHORT messageStartX = centerX - message.length() / 2;

	WriteConsoleOutputCharacter(output, message.c_str(), message.length(), {messageStartX, startingCursorY - 2}, &written);
}

// need to process wasd and arrow keys for selection and cursor movement
// numbers for board size selection
// enter or space for inputting a space
void processUserInput(HANDLE input, HANDLE output, Game& game, string& screenWindow)
{
	DWORD numEvents;
	GetNumberOfConsoleInputEvents(input, &numEvents);

	while (numEvents > 0)
	{
		INPUT_RECORD record;
		DWORD numRead;

		ReadConsoleInput(input, &record, 1,  &numRead);
		if (record.EventType == KEY_EVENT)
		{
			if (record.Event.KeyEvent.bKeyDown) // key released
			{
				int boardWidth, boardHeight, moves;
				// for cursor positioning after new game
				int breadth, depth, middleX, middleY, startingX, startingY;
				switch(record.Event.KeyEvent.uChar.AsciiChar)
				{
					case 'n':
						cursorX = 0;
						cursorY = 0;
						clearScreen(screenWindow);
						gameConcluded = false;
						getBoardSize(boardWidth, boardHeight);
						getMovesToWin(moves);
						game.newGame(boardWidth, boardHeight, moves);
							
						CONSOLE_SCREEN_BUFFER_INFO info;
						GetConsoleScreenBufferInfo(output, &info);
						breadth = game.width * 2 - 1;
						depth = game.height * 2 - 1;
						middleX = info.dwSize.X / 2;
						middleY = info.dwSize.Y / 2;
						startingX = middleX - breadth / 2;
						startingY = middleY - depth / 2;
						startingCursorX = startingX;
						startingCursorY = startingY;

						CONSOLE_CURSOR_INFO cursorInfo;
						cursorInfo.dwSize = 100;
						cursorInfo.bVisible = true;
						SetConsoleCursorInfo(output, &cursorInfo);
						SetConsoleCursorPosition(output, {(SHORT)startingCursorX, (SHORT)startingCursorY});

						break;
					case 'q':
						quitZeGame = true;
						break;
				}
				switch(record.Event.KeyEvent.wVirtualKeyCode)
				{
					case VK_UP:
						updateCursorPosition(0, -1, output, game);
						break;
					case VK_DOWN:
						updateCursorPosition(0, 1, output, game);
						break;
					case VK_LEFT:
						updateCursorPosition(-1, 0, output, game);
						break;
					case VK_RIGHT:
						updateCursorPosition(1, 0, output, game);
						break;
					case VK_SPACE:
					case VK_RETURN:
						game.inputMove(cursorX, cursorY);
						break;
				}
			}
		}
 		
		GetNumberOfConsoleInputEvents(input, &numEvents);
	}
}

// going to keep the cursor position in terms of the board
// then just convert to screen coordinates once rather than
// the other way around
void updateCursorPosition(int x, int y, HANDLE output, Game& game)
{
	cursorX += x;
	if (cursorX < 0)
		cursorX = game.width - 1;
	else if (cursorX >= game.width)
		cursorX = 0;
	cursorY += y;
	if (cursorY < 0)
		cursorY = game.height - 1;
	else if (cursorY >= game.height)
		cursorY = 0;

	// now convert to screen coordinates
	SHORT currentCursorX = startingCursorX + cursorX * 2;
	SHORT currentCursorY = startingCursorY + cursorY * 2;

	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = true;
	SetConsoleCursorInfo(output, &cursorInfo);
	SetConsoleCursorPosition(output, {(SHORT)currentCursorX, (SHORT)currentCursorY});
}

void drawBoard(HANDLE output, Game& game, string& consoleWindow)
{
	// need to get console info
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(output, &info);


	//string test2 = "hello there";
	//test.replace(HEIGHT/2 * WIDTH + WIDTH/2, test2.length(), test2);

	//DWORD chars;
	//WriteConsoleOutputCharacter(outputHandle, test.c_str(), test.length(), {0, 0}, &chars);
	
	// get board size from game
	int breadth = game.width * 2 - 1;
	int depth = game.height * 2 - 1;

	// find center
	int middleX = info.dwSize.X / 2;
	int middleY = info.dwSize.Y / 2;

	int startingX = middleX - breadth / 2;
	int startingY = middleY - depth / 2;

	startingCursorX = startingX;
	startingCursorY = startingY;


	string row = "";
	for (int i = 0; i < depth; i++)
	{
		row.clear();
		for (int j = 0; j < breadth; j++)
		{
			if (i % 2 == 0)
			{
				if (j % 2 == 0)
				{
					row.append(1, positionToChar(game.board[i/2][j/2]));
				}
				else
				{
					row.append(1, '|');
				}
			}
			else
			{
				row.append(1, '-');
				//if (j % 2 == 0)
				//	row.append(1, '_');
				//else
				//	row.append(1, '|');
			}
		}
		consoleWindow.replace(startingY * info.dwSize.X + startingX, row.length(), row);
		startingY++;
	}
	// translate between board size in game and string representing the screen buffer window
	DWORD chars;
	WriteConsoleOutputCharacter(output, consoleWindow.c_str(), consoleWindow.length(), {0,0}, &chars);
}

char positionToChar(Position pos)
{
	if (pos == Position::o)
		return 'O';
	else if (pos == Position::x)
		return 'X';
	else
		return ' ';
}

void setConsoleScreenBuffer(SHORT x, SHORT y)
{
	// screen buffer can't be smaller in either dimension than console window
	// screen buffer window can't be larger than screen buffer or screen(the entire monitor)
	// changing the window size of the active screen buffer changes the size of the console window
	// distinct nouns: screen buffer, screen buffer window, console window, screen
	
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT windowSize {0, 0, x - 1, y - 1};
	COORD bufferSize {x, y};
	SetConsoleScreenBufferSize(outputHandle, bufferSize);
	SetConsoleWindowInfo(outputHandle, true, &windowSize);
}

void outputInfo(CONSOLE_SCREEN_BUFFER_INFO& info)
{
	cout << "Size: " << info.dwSize.X << ", " << info.dwSize.Y << endl;
	cout << "cp: " << info.dwCursorPosition.X << ", " << info.dwCursorPosition.Y << endl;
	cout << "rect l,t,r,b: " << info.srWindow.Left << ", " << info.srWindow.Top << ", " << info.srWindow.Right << ", " << info.srWindow.Bottom << endl;
	cout << "max window size: " << info.dwMaximumWindowSize.X << ", " << info.dwMaximumWindowSize.Y << endl;
}

void potentiallyUsefulStuff()
{

	//HWND console = GetConsoleWindow();
	//RECT r;
	//GetWindowRect(console, &r);
	//MoveWindow(console, r.left, r.top, 1200, 800, TRUE);	
	//SMALL_RECT rect {0, 0, WIDTH, HEIGHT};
	//BOOL success = SetConsoleWindowInfo(outputHandle, true, &rect);

	//if (!success)
	//{
	//	DWORD error = ::GetLastError();
	//	std::string message = std::system_category().message(error);
	//	cout << "ERROR: " << message << endl;
	//}

	//SMALL_RECT windowSize = {0, 0, WIDTH - 1, HEIGHT - 1};
	//COORD bufferSize = {WIDTH, HEIGHT};
	//SetConsoleScreenBufferSize(outputHandle, bufferSize);
	//SetConsoleWindowInfo(outputHandle, true, &windowSize);
		
	//CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	//BOOL success = GetConsoleScreenBufferInfo(outputHandle, &bufferInfo); 	
	//if (!success)
	//{
	//	cout << "failed to get screen buffer info" << endl;
	//	return 0;
	//}
                                                                       
	//outputInfo(bufferInfo);
                                                                       
	//COORD maxSize = GetLargestConsoleWindowSize(outputHandle);
                                                                       
	//cout << "max size: " << maxSize.X << ", " << maxSize.Y << endl;
	//COORD size {WIDTH, HEIGHT};
	//success = SetConsoleScreenBufferSize(outputHandle, size);
	//cout << success << endl;
	//GetConsoleScreenBufferInfo(outputHandle, &bufferInfo);
	//outputInfo(bufferInfo);
	//system("pause");	
}
