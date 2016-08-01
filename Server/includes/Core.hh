#ifndef _CORE_HH__
# define _CORE_HH__

#include <string>
#include <vector>
#include <map>
#include <algorithm>

#ifdef _WIN32
#include "WDLLoader.hh"
#else
#include "UDLLoader.hh"
#include <cmath>
#include <unistd.h>
#endif
#include "ILevels.hh"
#include "Stage.hh"
#include "Object.hh"
#include "Player.hpp"

#include "Room.hh"

class Core;

typedef void(Core::* ptrMap)(int);

class Core
{
public:
	Core(Room *);
	~Core();

	bool loadRoom();
	void launchGame();
	bool launchLevel();
	IObject *checkCollision(IObject *);
	bool checkPosition();
	bool valueInRange(int, int, int);
	bool rectOverlap(IObject *, IObject *);
	void getPlayerEvent();
	void PlayerFire(int);
	void PlayerLeft(int);
	void PlayerRight(int);
	void PlayerUp(int);
	void PlayerDown(int);
	void PlayerInactive(int);
	bool sendUpdates(IObject *);
	bool sendUpdates(Player *);
	bool sendDeath(IObject *);
	IObject *checkCollision(Player *);
	bool rectOverlap(Player *, IObject *);
	bool sendDeath(Player *);
	bool sendEndGame();


private:
	IDLLoader *dll;
	ILevels *levels;
	IStage *stage;
	int _id;
	std::vector<IObject *> *_vobj;
	std::map<int, Player *> _players;
	bool _isAlive;
	std::map<int, ptrMap> mapPtr;
	Room *_room;
	int _score;
};


#endif // !_CORE_HH__
