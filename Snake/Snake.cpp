#include "pch.h"
#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>

#define width 30
#define height 20
using namespace std;

bool GameOver;
int x, y, foodX, foodY, score = 0;
int tailX[(width - 2)*(height - 2)];
int tailY[(width - 2)*(height - 2)];
int nTail = 0;
enum eDirection { STOP, LEFT, UP, RIGHT, DOWN };
eDirection dir;

void Setup()
{
	GameOver = false;
	dir = STOP;
	score = 0;
	x = width / 2;
	y = height / 2;
	srand(time(0));
	foodX = rand() % (width - 2) + 1;
	foodY = rand() % (height - 2) + 1;
}

void Draw()
{
	HANDLE hCon;
	COORD cPos;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	cPos.Y = 0;
	cPos.X = 0;
	SetConsoleCursorPosition(hCon, cPos);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i == 0 || i == height - 1)
				cout << "#";
			else
			{
				if (i == y && j == x)
					cout << "X";
				else if (j == 0 || j == width - 1)
					cout << "#";
				else if (i == foodY && j == foodX)
					cout << "o";
				else
				{
					bool print = false;
					for (int k = 0; k < nTail; k++)
					{
						if (tailX[k] == j && tailY[k] == i)
						{
							print = true;
							cout << "x";
						}
					}
					if(!print)
					cout << " ";
				}
			}
		}
		cout << endl;
	}
}

void Input()
{
	if (_kbhit())
		switch (toupper(_getch()))
		{
		case'A':
			if (dir == RIGHT)
				dir = RIGHT;
			else
				dir = LEFT;
			break;
		case'W':
			if (dir == DOWN)
				dir = DOWN;
			else
				dir = UP;
			break;
		case'D':
			if (dir == LEFT)
				dir = LEFT;
			else
				dir = RIGHT;
			break;
		case'S':
			if (dir == UP)
				dir = UP;
			else
				dir = DOWN;
			break;
		case'Q':
			GameOver = true;
			break;
		default:
			break;
		}
}

void Logic()
{
	if (x == foodX && foodY == y)
	{
		foodX = rand() % (width - 2) + 1;
		foodY = rand() % (height - 2) + 1;
		score += 10;
		nTail++;
	}
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;

		if (tailX[i] == foodX && tailY[i] == foodY)
		{
			cout << "x";
			foodX = rand() % (width - 2) + 1;
			foodY = rand() % (height - 2) + 1;
		}
	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case UP:
		y--;
		break;
	case RIGHT:
		x++;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	if (x == 0 || y == 0 || y == height - 1 || x == width - 1)
		GameOver = true;
	for (int k = 0; k < nTail; k++)
		if (tailX[k] == x && tailY[k] == y)
			GameOver = true;
	if (nTail + 1 == (width - 2)*(height - 2))
	{
		cout << endl << "You WIN!!!";
		exit(0);
	}
}

int main()
{
	Setup();
	while (!GameOver)
	{
		Draw();
		Input();
		Logic();
		cout << endl << "score: " << score;
		Sleep(50);
	}

	return 0;
}