#include <iostream>
#include <system_error>
#include <windows.h>
#include "game.h"

using namespace std;

#define WIDTH	150
#define HEIGHT	50

void setConsoleScreenBuffer(SHORT x, SHORT y);
void outputInfo(CONSOLE_SCREEN_BUFFER_INFO& info);
void processUserInput(HANDLE output);

int main()
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE inputHandle = GetStdHandle(STD_INPUT_HANDLE);

	setConsoleScreenBuffer(WIDTH, HEIGHT);	

	string test(WIDTH * HEIGHT, ' ');
	string test2 = "hello there";
	test.replace(HEIGHT/2 * WIDTH + WIDTH/2, test2.length(), test2);

	DWORD chars;
	WriteConsoleOutputCharacter(outputHandle, test.c_str(), test.length(), {0, 0}, &chars);

	int boardWidth = 3, boardHeight = 3;
	cout << "board width: ";
	cin >> boardWidth;
	cout << "board height: ";
	cin >> boardHeight;

	Game game;
	game.newGame(boardWidth, boardHeight);

	bool notQuit = true;
	while (notQuit)
	{
		processUserInput(outputHandle);
	}
}

void processUserInput(HANDLE output)
{
	DWORD numEvents;
	GetNumberOfConsoleInputEvents(output, &numEvents);

	if (numEvents > 0)
		cout << "there is user input" << endl;
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
