#include <vector>

using namespace std;

enum Position {x, o, blank};

class Game
{
public:
	void newGame(int boardWidth, int boardHeight);
	void inputMove(int x, int y);
	bool checkForWin();
	vector<vector<Position>> board;
private:
	Position playerToggle = Position::x;	
	void togglePlayer();
};
