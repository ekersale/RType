#ifndef __COREACTION_HH__
#define __COREACTION_HH__

#include <string>
#include <map>
#include <sstream>

#include "Thread.hh"
#include "Network.hh"
#include "Windows.hh"
#include "CoreGame.hh"
#include "Shared.hh"

//#define PORT "2000"
//#define ADDRESS "10.13.253.138"  //"10.13.253.222"  "10.13.253.222" "10.13.253.142" "10.13.253.109" "10.13.253.98" 
//#define ADDRESS "10.13.253.98"
//#define ROOMNAME "cocu\0"

class CoreAction;

class CoreAction : public Thread
{
public:
	CoreAction();
	~CoreAction();

	void	runCode(void *parameters);
	std::string	intToString();
	std::string	intToString(unsigned int value);

	//Getter
	int	getRoomPort(void) const;
	Network *getSocketInGame(void) const;
	Shared	*getClassShared(void) const;

	//Setter 
	void setRoomPort(int port);
	void setSocketInGame(Network *socket);
	void setClassShared(Shared *sharedClass);

	void	addPlayer(t_reception *, std::map<int, t_reception> mapPlayer);
	void	addAmmo(t_reception *, std::map<int, t_reception> mapAmmo);
	void	addMonster(t_reception *, std::map<int, t_reception> mapMonster);
	void	addBoss(t_reception *, std::map<int, t_reception> mapBoss);
	void	endParty(t_reception *, std::map<int, t_reception> mapVictory);

private:	
	int		_roomPort;
	Network	*_socketInGame;
	Shared	*_classShared;
	Sound *_classSound;

	/*std::map<int, t_reception>	_mapPlayer;
	std::map<int, t_reception>	_mapAmmo;
	std::map<int, t_reception>	_mapMonster;
	std::map<int, t_reception>	_mapBoss;*/
};

#endif // !_COREACTION_HH__
