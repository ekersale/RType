#ifndef __SHARED_HH__
#define __SHARED_HH__

#include	<map>
#include	<vector>

//#include	"CoreGame.hh"


enum {
	CLIENT = 0,
	IP = 1,
	CO = 2,
	END = 3,
	PLAYER = 4,
	AMMO1 = 5,
	AMMO2 = 6,
	AMMO3 = 7,
	AMMO4 = 8,
	MONSTER1 = 9,
	MONSTER2 = 10,
	MONSTER3 = 11,
	MONSTER4 = 12,
	BOSS1 = 13,
	BOSS2 = 14,
	BOSS3 = 15
};

typedef struct s_reception
{
	unsigned int id;
	char type;
	char alive;
	unsigned int pos[2];//<pos.x & pos.y>;
	unsigned long network[2];
}				t_reception;


typedef struct s_movement
{
	char actions; // <1 | 2 | 3 | 4>;
}				t_movement;

typedef struct s_explosion {
	int i;
	int pos[2];
}				t_explosion;

class Shared
{
public:
	Shared();
	~Shared();

	//Getters
	std::map<int, t_reception>	getMapPlayer() const;
	std::map<int, t_reception>	getMapAmmo() const;
	std::map<int, t_reception>	getMapMonster() const;
	std::map<int, t_reception>	getMapBoss() const;


	std::map<int, t_reception>	_mapPlayer;
	std::map<int, t_reception>	_mapAmmo;
	std::map<int, t_reception>	_mapMonster;
	std::map<int, t_reception>	_mapBoss;	

	std::vector<unsigned int>	_idDeathPlayer;
	std::vector<unsigned int>	_idDeathObject;

	bool							_victory;
	std::string						_score;
	std::vector<t_explosion *>		_vexplosion;
};

typedef struct s_sconnect {
	std::string		ip;
	std::string		roomname;
	std::string		port;
} t_sconnect;

extern t_sconnect _sconnect;


#endif // !__SHARED_HH__7



