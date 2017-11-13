#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
using namespace std;

#define ctrl_types 3
enum ctrl_id{ EMPTY, HUMAN, AI };
const string ctrl_str[] = { "Empty", "Human", " Ai  " };

class Player
{
private:
	int control;
	vector<int> card;
	int target[3];

public:
	Player(int ctrl);
	friend class Game;
};



#endif
