#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <Windows.h>
#include "Player.h"
using namespace std;

const string tiki_str[] = { "(OuO')", "(;ω;)", "˙A˙|", "(T.T )", "(QAQ) ", "˙__˙", "  囧  ", " ^w^  ", "(= = )" };

class Game
{
private:
	int round;
	int player_num;
	int user;
	Player* players[4];
	vector<int> tiki;

public:
	void init(int *ctrl);
	int GameLoop();

	int selectCard();
	int selectTiki(int card, int ctrl);
	void showPlayerCard(int p);
	void showTiki();
	void showTarget(int x, int y, int p);
	void cleanMessage();
	void showCard(pair<int, int> *pos, int id);
	void showTiki(int x, int y);
};


inline void gotoxy(int xpos, int ypos)
{
	static HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD scrn;
	scrn.X = xpos;
	scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}


#endif
