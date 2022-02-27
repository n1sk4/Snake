#include "SnakeGame.h"

SnakeGame::SnakeGame() {
	MainMenuMode();
	if (!mainMenuRunning) {
		normalGameRunning = true;
		GameModeNormal();
	}
}

	void SnakeGame::Setup() {
		Direction = STOP;
		SetIncrement(1);
		SetSpeed(50);
		Place();
		Score = 0;
	}

	void SnakeGame::Place() {
		RandomPlacement();
		//Target and player on top
		while (X == TargetX && Y == TargetY) {
			RandomPlacement();
		}
		while (X == 0 || Y == 0 || X == width - 1 || Y == height - 1) {
			RandomPlacement();
		}
	}

	void SnakeGame::RandomPlacement() {
		PlaceFruit();
		PlaceSnake();
	}

	void SnakeGame::PlaceFruit() {
		TargetX = rand() % width;
		TargetY = rand() % height;
	}

	void SnakeGame::PlaceSnake() {
		X = rand() % width;
		Y = rand() % height;
	}

	void SnakeGame::PlaceTail() {
		fPosX = TailX[0];
		fPosY = TailY[0];
		TailX[0] = X;
		TailY[0] = Y;
		for (int i = 1; i < TailLength; i++) {
			sPosX = TailX[i];
			sPosY = TailY[i];
			TailX[i] = fPosX;
			TailY[i] = fPosY;
			fPosX = sPosX;
			fPosY = sPosY;
		}
	}

	void SnakeGame::SetSpeed(int sleepTime) {
		Speed = sleepTime;
	}

	void SnakeGame::SetIncrement(int inc) {
		IncSnake = inc;
	}

	void SnakeGame::Window() {
		system("cls");
		CreateTopHorizontalBorder();
		CreateBody();
		CreateBotHorizontalBorder();
		cout << "SCORE " << Score;
	}

	void SnakeGame::CreateBody() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (j == 0 || j == width - 1) {
					cout << char(VER_BORDER);
				}
				else if (i == Y && j == X) {
					cout << char(SNAKE_HEAD);
				}
				else if (i == TargetY && j == TargetX) {
					cout << char(FRUIT);
				}
				else {
					bool tail = false;
					for (int k = 0; k < TailLength; k++) {
						if (j == TailX[k] && i == TailY[k]) {
							cout << char(SNAKE_TAIL);
							tail = true;
						}
					}
					if (!tail) {
						cout << " ";
					}
				}

			}
			cout << endl;
		}
	}

	void SnakeGame::CreateMenuBody() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (j == 0 || j == width - 1) {
					cout << char(VER_BORDER);
				}
				else if (i == floor(height / 2) && j == floor(width/2 - 6)) {
					cout << "SNAKE GAME";
					j += 9;
				}
				else {
					cout << " ";
				}
			}
			cout << endl;
		}
	}

	void SnakeGame::CreateTopHorizontalBorder() {
		cout << char(TOP_L_ANGLE);
		for (int i = 1; i < width - 1; i++) {
			cout << char(HOR_BORDER);
		}
		cout << char(TOP_R_ANGLE);
		cout << endl;
	}

	void SnakeGame::CreateBotHorizontalBorder() {
		cout << char(BOT_L_ANGLE);
		for (int i = 1; i < width-1; i++) {
			cout << char(HOR_BORDER);
		}
		cout << char(BOT_R_ANGLE);
		cout << endl;
	}

	void SnakeGame::Input() {
		if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('a') || GetAsyncKeyState('A') && Direction != RIGHT) {
			Direction = LEFT;
		}
		else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('d') || GetAsyncKeyState('D') && Direction != LEFT) {
			Direction = RIGHT;
		}
		else if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('w') || GetAsyncKeyState('W') && Direction != DOWN) {
			Direction = UP;
		}
		else if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('s') || GetAsyncKeyState('S') && Direction != UP) {
			Direction = DOWN;
		}
	}

	void SnakeGame::MoveSnake() {
		switch (Direction){
		case LEFT:
			X -= IncSnake;
			break;
		case RIGHT:
			X += IncSnake;
			break;
		case UP:
			Y -= IncSnake;
			break;
		case DOWN:
			Y += IncSnake;
			break;
		}
	}

	void SnakeGame::GameOver() {
		SnakeBorderHit();
		SnakeTailHit();
		ExitKeyHit();
	}

	void SnakeGame::SnakeBorderHit() {
		if (X >= width - 1 || X <= 0 || Y < 0 || Y >= height) {
			normalGameRunning = false;
		}
	}

	void SnakeGame::SnakeTailHit() {
		for (int i = 1; i < TailLength; i++) {
			if (X == TailX[i] && Y == TailY[i]) {
				normalGameRunning = false;
			}
		}
	}

	void SnakeGame::ExitKeyHit() {
		if (GetAsyncKeyState('X') || GetAsyncKeyState(VK_ESCAPE)) {
			normalGameRunning = false;
			mainMenuRunning = true;
		}
	}

	void SnakeGame::GrowSnake() {
		if (X == TargetX && Y == TargetY) {
			PlaceFruit();
			TailLength++;
			Score++;
		}
	}

	void SnakeGame::GameModeNormal() {
		Setup();
		while (normalGameRunning) {
			Window();
			Input();
			MoveSnake();
			GrowSnake();
			PlaceTail();
			GameOver();
			Sleep(Speed);
		}
	}

	void SnakeGame::MainMenuMode() {
		mainMenuRunning = true;
		while (mainMenuRunning) {
			system("cls");
			CreateTopHorizontalBorder();
			CreateMenuBody();
			CreateBotHorizontalBorder();
			cout << endl;
			cout << "Press SPACE to Start!";
			if (GetAsyncKeyState(VK_SPACE)) {
				mainMenuRunning = false;
			}
			if (GetAsyncKeyState(VK_ESCAPE)) {
				mainMenuRunning = false;
				normalGameRunning = false;
				exit(3);
			}
		}
	}