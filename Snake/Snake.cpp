﻿#include "pch.h"
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
		switch (_getch())
		{
		case'a':
		case'A':
			if (dir == RIGHT)
				dir = RIGHT;
			else
				dir = LEFT;
			break;
		case'w':
		case'W':
			if (dir == DOWN)
				dir = DOWN;
			else
				dir = UP;
			break;
		case'd':
		case'D':
			if (dir == LEFT)
				dir = LEFT;
			else
				dir = RIGHT;
			break;
		case's':
		case'S':
			if (dir == UP)
				dir = UP;
			else
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

	if (x == foodX && foodY == y)
	{
		foodX = rand() % (width - 2) + 1;
		foodY = rand() % (height - 2) + 1;
		score += 10;
		nTail++;
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
	}

	return 0;
}