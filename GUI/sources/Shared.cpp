#include "Shared.hh"


Shared::Shared()
{
	_victory = false;
}


Shared::~Shared()
{
}

std::map<int, t_reception>	Shared::getMapPlayer() const
{
	return this->_mapPlayer;
}

std::map<int, t_reception>	Shared::getMapAmmo() const
{
	return this->_mapAmmo;
}

std::map<int, t_reception>	Shared::getMapMonster() const
{
	return this->_mapMonster;
}
std::map<int, t_reception>	Shared::getMapBoss() const
{
	return this->_mapBoss;
}