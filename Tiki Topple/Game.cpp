#include "Game.h"

#define SLEEP_TIME 500

//card_pos
inline pair<int, int> player_pos(int x){
	return make_pair(x * 12 + 2, 2);
}
#define tiki_X 2
#define tiki_Y 30


void Game::init(int *ctrl)
{
	player_num = 0;
	for (int i = 0; i < 4; i++)
	{
		if (ctrl[i] == HUMAN){
			user = i;
		}
		if (ctrl[i] != EMPTY){
			player_num++;
			players[i] = new Player(ctrl[i]);
			players[i]->target[0] = rand() % 9;
			do{
				players[i]->target[1] = rand() % 9;
			} while (players[i]->target[0] == players[i]->target[1]);
			do{
				players[i]->target[2] = rand() % 9;
			} while (players[i]->target[1] == players[i]->target[2] || players[i]->target[0] == players[i]->target[2]);
			if (ctrl[i] == HUMAN){
				showPlayerCard(i);
				showTarget(90, 2, i);
			}
		}
		else{
			players[i] = NULL;
		}
	}
	tiki.resize(9);
	for (int i = 0; i < 9; i++){
		tiki[i] = i;
	}
	gotoxy(tiki_X, tiki_Y - 1);
	cout << "   No.1      No.2      No.3";
}

int Game::selectCard()
{
	int kb, select = 0, item = 8 - round;
	gotoxy(7, 10);
	cout << "△";
	while (1)
	{
		gotoxy(select * 12 + 7, 10);
		cout << "△";
		kb = getch();
		gotoxy(select * 12 + 7, 10);
		cout << "  ";
		switch (kb)
		{
		case 75: //左
			select += item - 1;
			select %= item;
			break;
		case 77: //右
			select += 1;
			select %= item;
			break;
		case 32: //Space
			return select;
		}
	}
}

int Game::selectTiki(int card, int ctrl)
{
	int kb, select = 0, item = tiki.size(), from;
	if (card == 1){
		from = 1;
	}
	else if (card == 2){
		from = 2;
	}
	else if (card == 3){
		from = 3;
	}
	else if (card == 4){
		from = 0;
	}
	else if (card == 5){
		from = item - 1;
	}
	item -= from;
	if (ctrl == AI){
		return from + rand() % item;
	}
	while (ctrl == HUMAN)
	{
		gotoxy((select + from) * 10 + tiki_X + 4, tiki_Y + 6);
		cout << "△";
		kb = getch();
		gotoxy((select + from) * 10 + tiki_X + 4, tiki_Y + 6);
		cout << "  ";
		switch (kb)
		{
		case 75: //左
			select += item - 1;
			select %= item;
			break;
		case 77: //右
			select += 1;
			select %= item;
			break;
		case 32: //Space
			return select + from;
		case 98: //b
			return -1;
		}
	}
}

void Game::showCard(pair<int, int> *pos, int id)
{
	if (id == 0)
	{
		for (int i = 0; i<8; i++)
		{
			gotoxy(pos->first, pos->second + i);
			cout << "           ";
		}
	}
	else
	{
		gotoxy(pos->first, pos->second);
		cout << "┌────┐ ";
		if (id <= 3){
			gotoxy(pos->first, pos->second + 1);
			cout << "│指定堤基│ ";
			gotoxy(pos->first, pos->second + 2);
			cout << "│   +" << id << "   │";
		}
		else if (id == 4){
			gotoxy(pos->first, pos->second + 1);
			cout << "│推倒堤基│ ";
			gotoxy(pos->first, pos->second + 2);
			cout << "│        │ ";
		}
		else if (id == 5){
			gotoxy(pos->first, pos->second + 1);
			cout << "│殺死堤基│ ";
			gotoxy(pos->first, pos->second + 2);
			cout << "│   X    │ ";
		}
		for (int i = 1; i<3; i++)
		{
			gotoxy(pos->first, pos->second + 2 * i + 1);
			cout << "│        │ ";
			gotoxy(pos->first, pos->second + 2 * i + 2);
			cout << "│        │ ";
		}
		gotoxy(pos->first, pos->second + 7);
		cout << "└────┘ ";
	}
}

void Game::showPlayerCard(int p)
{
	int i;
	for (i = 0; i < players[p]->card.size(); i++){
		showCard(&player_pos(i), players[p]->card[i]);
	}
	if (i < 7){
		showCard(&player_pos(i), 0);
	}
}

void Game::showTiki()
{
	gotoxy(tiki_X, tiki_Y);
	for (int j = 0; j < tiki.size(); j++){
		cout << "┌───┐";
	}
	gotoxy(tiki_X, tiki_Y + 1);
	for (int j = 0; j < tiki.size(); j++){
		cout << "│      │";
	}
	gotoxy(tiki_X, tiki_Y + 2);
	for (int j = 0; j < tiki.size(); j++){
		cout << "│" << tiki_str[tiki[j]] << "│";
	}
	gotoxy(tiki_X, tiki_Y + 3);
	for (int j = 0; j < tiki.size(); j++){
		cout << "│      │";
	}
	gotoxy(tiki_X, tiki_Y + 4);
	for (int j = 0; j < tiki.size(); j++){
		cout << "│      │";
	}
	gotoxy(tiki_X, tiki_Y + 5);
	for (int j = 0; j < tiki.size(); j++){
		cout << "└───┘";
	}
}

void Game::showTarget(int x, int y, int p)
{
	gotoxy(x, y);
	cout << "┌─────┐";
	gotoxy(x, y + 1);
	cout << "│ Mission  │";
	gotoxy(x, y + 2);
	cout << "│No.1:   +9│";
	gotoxy(x, y + 3);
	cout << "│" << tiki_str[players[p]->target[0]] << "    │";
	gotoxy(x, y + 4);
	cout << "│          │";
	gotoxy(x, y + 5);
	cout << "│No.2 up:+5│";
	gotoxy(x, y + 6);
	cout << "│" << tiki_str[players[p]->target[1]] << "    │";
	gotoxy(x, y + 7);
	cout << "│          │";
	gotoxy(x, y + 8);
	cout << "│No.3:up:+2│";
	gotoxy(x, y + 9);
	cout << "│" << tiki_str[players[p]->target[2]] << "    │";
	gotoxy(x, y + 10);
	cout << "│          │";
	gotoxy(x, y + 11);
	cout << "└─────┘";
}

int Game::GameLoop()
{
	int sel_cardpos, sel_card, sel_tiki;

	if (player_num == 0){
		return -102;
	}
	showTiki();
	for (round = 1; round <= 7 && tiki.size() > 3; round++)
	{
		gotoxy(2, 0);
		cout << "Round " << round;
		for (int i = 0; i < 4; i++)
		{
			if (players[i] == NULL){
				continue;
			}
			if (players[i]->control == HUMAN)
			{
				gotoxy(10, 0);
				cout << "換你選牌            ";
				do{
					sel_cardpos = selectCard();
					sel_card = players[i]->card[sel_cardpos];
					sel_tiki = selectTiki(sel_card, HUMAN);
				} while (sel_tiki == -1);
				players[i]->card.erase(players[i]->card.begin() + sel_cardpos);
				showPlayerCard(i);
			}
			else if (players[i]->control == AI)
			{
				sel_cardpos = rand() % (8 - round);
				sel_card = players[i]->card[sel_cardpos];
				sel_tiki = selectTiki(sel_card, AI);
				players[i]->card.erase(players[i]->card.begin() + sel_cardpos);
			}

			gotoxy(37, 15);
			cout << "Player " << i + 1 << " 對 " << tiki_str[tiki[sel_tiki]] << " 使用";
			showCard(&make_pair(42, 16), sel_card);
			gotoxy(10, 0);

			Sleep(SLEEP_TIME);
			if (sel_card <= 3){
				int buf = tiki[sel_tiki];
				tiki.erase(tiki.begin() + sel_tiki);
				tiki.insert(tiki.begin() + sel_tiki - sel_card, buf);
				showTiki();
			}
			else if (sel_card == 4){
				int buf = tiki[sel_tiki];
				tiki.erase(tiki.begin() + sel_tiki);
				tiki.push_back(buf);
				showTiki();
			}
			else if (sel_card == 5){
				tiki.pop_back();
				for (int j = 0; j < 6; j++){
					gotoxy(tiki_X + 10 * tiki.size(), tiki_Y + j); cout << "          ";
				}
			}

			if (tiki.size() <= 3){
				break;
			}
		}
	}

	//遊戲結束
	int point[4], user_point = -1, no = player_num;
	system("cls");
	cout << "  遊戲結束";
	showTiki();
	gotoxy(tiki_X, tiki_Y - 1);
	cout << "   No.1      No.2      No.3";
	for (int i = 0; i < 4; i++)
	{
		if (players[i] != NULL)
		{
			gotoxy(6 + 18 * i, 4);
			cout << "Player " << i + 1;
			showTarget(4 + 18 * i, 5, i);
			point[i] = 0;
			if (players[i]->target[0] == tiki[0]){
				point[i] += 9;
			}
			if (players[i]->target[1] == tiki[1] || players[i]->target[1] == tiki[0]){
				point[i] += 5;
			}
			if (players[i]->target[2] == tiki[2] || players[i]->target[2] == tiki[1] || players[i]->target[2] == tiki[0]){
				point[i] += 2;
			}
			gotoxy(6 + 18 * i, 18);
			cout << "Point : " << point[i];
			if (players[i]->control == HUMAN){
				user_point = point[i];
			}
		}
	}
	for (int i = 0; i < 4; i++){
		if (user_point >= point[i] && point[i] >= 0){
			no--;
		}
	}
	no++; //自己
	gotoxy(12, 0);
	cout << "第 " << no << "名   ";
	system("pause");
	return player_num - no;
}
