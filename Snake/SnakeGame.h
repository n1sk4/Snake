#include <iostream>
#include <Windows.h>

using namespace std;

enum direction { STOP = 0, UP, DOWN, LEFT, RIGHT };

const int SNAKE_HEAD  = 219;
const int SNAKE_TAIL  = 254;
const int FRUIT		  = 176;
const int HOR_BORDER  = 205;
const int VER_BORDER  = 186;
const int TOP_R_ANGLE = 187;
const int TOP_L_ANGLE = 201;
const int BOT_R_ANGLE = 188;
const int BOT_L_ANGLE = 200;

class SnakeGame {
public:
	SnakeGame();
private:
	const int height = 25;
	const int width = 50;
	bool mainMenuRunning;
	bool normalGameRunning;
	int X;
	int Y;
	int TailX[100];
	int TailY[100];
	int fPosX;
	int fPosY;
	int sPosX;
	int sPosY;
	int TailLength = 1;
	int TargetX;
	int TargetY;
	int Score;
	int IncSnake;
	int Speed;
	direction Direction;
	void Setup();
	void Place();
	void RandomPlacement();
	void PlaceFruit();
	void PlaceSnake();
	void PlaceTail();
	void SetSpeed(int sleepTime);
	void SetIncrement(int inc);
	void Window();
	void CreateBody();
	void CreateMenuBody();
	void CreateTopHorizontalBorder();
	void CreateBotHorizontalBorder();
	void Input();
	void MoveSnake();
	void GameOver();
	void SnakeBorderHit();
	void SnakeTailHit();
	void ExitKeyHit();
	void GrowSnake();
	void GameModeNormal();
	void MainMenuMode();
};
