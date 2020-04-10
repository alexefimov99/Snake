#include "pch.h"
#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>

#define width 30
#define height 20
using namespace std;

bool GameOver;
int x, y, foodX, foodY, score;
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
	system("cls");
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
				else if (i == foodY && j == foodX)
					cout << "o";
				else if (j == 0 || j == width - 1)
					cout << "#";
				else
					cout << " ";
			}
		}
		cout << endl;
	}
}

void Input()
{
	if (_kbhit())
		switch (_getch())
		{
		case'a':
		case'A':
			dir = LEFT;
			break;
		case'w':
		case'W':
			dir = UP;
			break;
		case'd':
		case'D':
			dir = RIGHT;
			break;
		case's':
		case'S':
			dir = DOWN;
			break;
		case'q':
		case'Q':
			GameOver = true;
			break;
		default:
			break;
		}
}

void Logic()
{
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

	if (x == foodX && foodY == y)
	{
		foodX = rand() % (width - 2) + 1;
		foodY = rand() % (height - 2) + 1;

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
	}

	return 0;
}