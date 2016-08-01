#include "CoreAction.hh"

CoreAction::CoreAction()
{
	_classSound = new Sound;
	_classSound->init();
}

CoreAction::~CoreAction()
{
}

void	CoreAction::runCode(void *params)
{
	std::string	port = intToString();
	t_reception	  *recv;

	this->_socketInGame->bindSocket(port.c_str());

	while (1)
	{
		this->_socketInGame->recvFromSocket();
		
		recv = (t_reception *)this->_socketInGame->get_buffer();

		if (recv->type >= 9 && recv->type <= 12)
			this->addMonster(recv, this->_classShared->_mapMonster);

		if (recv->type >= 13 && recv->type <= 15)
			this->addBoss(recv, this->_classShared->_mapBoss);

		if (recv->type >= 5 && recv->type <= 8)
			this->addAmmo(recv, this->_classShared->_mapAmmo);

		if (recv->type == 4)
			this->addPlayer(recv, this->_classShared->_mapPlayer);

		if (recv->type == 3)
		{
			std::cout << "La partie se termine " << std::endl;
			this->endParty(recv, this->_classShared->_mapPlayer);
		}
	}
}

int			CoreAction::getRoomPort(void) const
{
	return this->_roomPort;
}

void		CoreAction::setRoomPort(int port)
{
	this->_roomPort = port;
}

Network 	*CoreAction::getSocketInGame() const
{
	return this->_socketInGame;
}

void		CoreAction::setSocketInGame(Network *socket)
{
	this->_socketInGame = socket;
}

Shared	*CoreAction::getClassShared() const
{
	return this->_classShared;
}

void		CoreAction::setClassShared(Shared *obj)
{
	this->_classShared = obj;
}

std::string	CoreAction::intToString()
{
	std::stringstream       ss;
	std::string             stringPort;

	ss << this->_roomPort;
	stringPort = ss.str();

	return stringPort;
}

std::string	CoreAction::intToString(unsigned int value)
{
	std::stringstream       ss;
	std::string             stringTmp;

	ss << value;
	stringTmp = ss.str();

	return stringTmp;
}

void	CoreAction::addPlayer(t_reception *structure, std::map<int, t_reception> mapPlayer)
{
	if (structure->alive == 0)
	{
		t_explosion *tmp = new t_explosion;
		tmp->i = 8;
		tmp->pos[0] = structure->pos[0];
		tmp->pos[1] = structure->pos[1];
		this->_classShared->_vexplosion.push_back(tmp);
		this->_classShared->_idDeathPlayer.push_back(structure->id);
	}
	if (this->_classShared->_mapPlayer.find(structure->id) != this->_classShared->_mapPlayer.end())
	{
		this->_classShared->_mapPlayer[structure->id].pos[0] = structure->pos[0];
		this->_classShared->_mapPlayer[structure->id].pos[1] = structure->pos[1];
		this->_classShared->_mapPlayer[structure->id].alive = structure->alive;
	}
	else
		this->_classShared->_mapPlayer.insert(std::pair<int, t_reception>(structure->id, *structure));
}
void	CoreAction::addAmmo(t_reception *structure, std::map<int, t_reception> mapAmmo)
{
	if (structure->alive == 0)
		this->_classShared->_idDeathObject.push_back(structure->id);

	if ((this->_classShared->_mapAmmo.find(structure->id)) != this->_classShared->_mapAmmo.end())
	{
		this->_classShared->_mapAmmo[structure->id].pos[0] = structure->pos[0];
		this->_classShared->_mapAmmo[structure->id].pos[1] = structure->pos[1];
		this->_classShared->_mapAmmo[structure->id].alive = structure->alive;
	}
	else {
		if (structure->id == PLAYER)
			_classSound->playSound("shoot");
		this->_classShared->_mapAmmo.insert(std::pair<int, t_reception>(structure->id, *structure));
	}
}

void	CoreAction::addMonster(t_reception *structure, std::map<int, t_reception> mapMonster)
{	
	if (structure->alive == 0) {
		t_explosion *tmp = new t_explosion;
		tmp->i = 8;
		tmp->pos[0] = structure->pos[0];
		tmp->pos[1] = structure->pos[1];
		this->_classShared->_vexplosion.push_back(tmp);
		_classSound->playSound("explosion");
		this->_classShared->_idDeathObject.push_back(structure->id);
	}

	if ((this->_classShared->_mapMonster.find(structure->id)) != this->_classShared->_mapMonster.end())
	{
		this->_classShared->_mapMonster[structure->id].pos[0] = structure->pos[0];
		this->_classShared->_mapMonster[structure->id].pos[1] = structure->pos[1];
		this->_classShared->_mapMonster[structure->id].alive = structure->alive;
	}
	else
		this->_classShared->_mapMonster[structure->id] = *structure;
}

void	CoreAction::addBoss(t_reception *structure, std::map<int, t_reception> mapBoss)
{
	if (structure->alive == 0) {
		t_explosion *tmp = new t_explosion;
		tmp->i = 8;
		tmp->pos[0] = structure->pos[0];
		tmp->pos[1] = structure->pos[1];
		this->_classShared->_vexplosion.push_back(tmp);
		this->_classShared->_idDeathObject.push_back(structure->id);
	}
	if ((this->_classShared->_mapBoss.find(structure->id)) != this->_classShared->_mapBoss.end())
	{
		this->_classShared->_mapBoss[structure->id].pos[0] = structure->pos[0];
		this->_classShared->_mapBoss[structure->id].pos[1] = structure->pos[1];
		this->_classShared->_mapBoss[structure->id].alive = structure->alive;
	}
	else
		this->_classShared->_mapBoss.insert(std::pair<int, t_reception>(structure->id, *structure));
}

void	CoreAction::endParty(t_reception *recv, std::map<int, t_reception> mapVictory)
{
	std::string	 tmp;

	tmp = this->intToString(recv->id);
	tmp = intToString(recv->id);
	this->_classShared->_victory = true;
	this->_classShared->_score = tmp;
}
