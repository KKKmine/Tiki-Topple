//
//                        推倒堤基   v1.00
//                                                   by KKKmine  2016/4/13

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "Game.h"
#include "Player.h"
using namespace std;

#define VER "v1.00"

#define menu_posX 50
#define menu_posY 6

void init_console();
void menu(int* ctrl);

int main(int argc, char* argv[])
{
	Game game;
	int ctrl[4], point;

	init_console();

	while (1) {
		menu(ctrl);
		game.init(ctrl);
		point = game.GameLoop();
	}

	return 0;
}


void init_console()
{
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	 
	COORD buf_size = { 110, 50 };
	SMALL_RECT win_rect = { 0, 0, buf_size.X - 1, 40 - 1 };
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hOuput, &info);
	info.dwSize = buf_size;
	info.srWindow = win_rect;
	SetConsoleScreenBufferSize(hOuput, buf_size);
	SetConsoleWindowInfo(hOuput, true, &win_rect);

	_CONSOLE_CURSOR_INFO  cursor_info;
	GetConsoleCursorInfo(hOuput, &cursor_info);
	cursor_info.bVisible = false;
	SetConsoleCursorInfo(hOuput, &cursor_info);
	SetConsoleTitle(L"推倒堤基");

	srand(time(NULL));
}


void menu(int *ctrl)
{
	int kb, select = 0, isHuman = false;
	memset(ctrl, EMPTY, sizeof(int)* 4);

	system("cls");
	gotoxy(0, 1);
	cout << "                             _____ __ _ ___ __     _____ _____ _____ _____ __    _____ " << endl;
	cout << "                            |_   _|  | |  _|  |   |_   _|     |  _  |  _  |  |  |   __|" << endl;
	cout << "                              | | |  |   |_|  |     | | |  |  |  ___|  ___|  |__|   __|" << endl;
	cout << "                              |_| |__|_|___|__|     |_| |_____|_|   |_|   |_____|_____|" << endl;
	for (int i = 0; i < 4; i++)
	{
		gotoxy(menu_posX, menu_posY + 4 * i); cout << "Player : " << i + 1;
		gotoxy(menu_posX + 3 , menu_posY + 1 + 4 * i); cout << ctrl_str[ctrl[i]];
	}
	gotoxy(100, 38);
	cout << VER;

	while (1)
	{
		gotoxy(menu_posX, menu_posY + 1 + 4 * select); cout << "<";
		gotoxy(menu_posX + 10, menu_posY + 1 + 4 * select); cout << ">";
		kb = getch();
		switch (kb)
		{
		case 72: //上
			gotoxy(menu_posX, menu_posY + 1 + 4 * select); cout << " ";
			gotoxy(menu_posX + 10, menu_posY + 1 + 4 * select); cout << " ";
			select += 4 - 1; select %= 4;
			break;
		case 80: //下
			gotoxy(menu_posX, menu_posY + 1 + 4 * select); cout << " ";
			gotoxy(menu_posX + 10, menu_posY + 1 + 4 * select); cout << " ";
			select += 1; select %= 4;
			break;
		case 75: //左
			if (ctrl[select] == HUMAN){
				isHuman = false;
			}
			ctrl[select] += ctrl_types - 1; ctrl[select] %= ctrl_types;
			if (isHuman&&ctrl[select] == HUMAN){
				ctrl[select]--;
			}
			gotoxy(menu_posX + 3, menu_posY + 1 + 4 * select); cout << ctrl_str[ctrl[select]];
			if (ctrl[select] == HUMAN){
				isHuman = true;
			}
			break;
		case 77: //右
			if (ctrl[select] == HUMAN){
				isHuman = false;
			}
			ctrl[select] += 1; ctrl[select] %= ctrl_types;
			if (isHuman&&ctrl[select] == HUMAN){
				ctrl[select]++;
			}
			gotoxy(menu_posX + 3, menu_posY + 1 + 4 * select); cout << ctrl_str[ctrl[select]];
			if (ctrl[select] == HUMAN){
				isHuman = true;
			}
			break;
		case 32: //Space
			gotoxy(menu_posX, menu_posY + 1 + 4 * select); cout << " ";
			gotoxy(menu_posX + 10, menu_posY + 1 + 4 * select); cout << " ";
			system("cls");
			return;
		}
	}
}