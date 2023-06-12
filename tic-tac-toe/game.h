#include <vector>

using namespace std;

enum Position {x, o, blank};
enum Result {None, Cats, X_WINS, O_WINS};

class Game
{
public:
	void newGame(int boardWidth, int boardHeight, int moves);
	void inputMove(int x, int y);
	vector<vector<Position>> board;
	Result gameResultStatus = Result::None;
	int width = 0, height = 0;
	int movesToWin = 0;
private:
	Position playerToggle = Position::x;	
	void checkForWinOrCats();
	bool checkHorizontal(Position pos);
	bool checkVertical(Position pos);
	bool checkDiagonal(Position pos);
	void togglePlayer();
	int numMoves = 0;
};
