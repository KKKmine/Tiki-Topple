#include "Player.h"


Player::Player(int ctrl)
{
	control = ctrl;
	card.resize(7);
	card[0] = 1;
	card[1] = 1;
	card[2] = 2;
	card[3] = 3;
	card[4] = 4;
	card[5] = 5;
	card[6] = 5;
}