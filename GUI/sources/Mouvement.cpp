#include "CoreGame.hh"
#include "MTime.hh"

#include	<string>


void		CoreGame::moveLeft(t_movement mouv)
{
	char	value;

	value = 1;
	this->_socketInGame->sendToSocket(this->_idSocketRoom, (void *)&value, strlen("1"));
}

void		CoreGame::moveRight(t_movement mouv)
{
	char	value;

	value = 2;
	this->_socketInGame->sendToSocket(this->_idSocketRoom, (void *)&value, strlen("2"));
}

void		CoreGame::moveUp(t_movement mouv)
{
	char	value;

	value = 3;
	this->_socketInGame->sendToSocket(this->_idSocketRoom, (void *)&value, strlen("3"));
}

void		CoreGame::moveDown(t_movement mouv)
{
	char	value;

	value = 4;
	this->_socketInGame->sendToSocket(this->_idSocketRoom, (void *)&value, strlen("4"));
}

void		CoreGame::shoot(t_movement mouv)
{
	char		value;
	static int frequencyShoot;

	value = 5;
	frequencyShoot++;
	if (frequencyShoot % 8 == 0){
		_sound->playMusic("shoot", true);
		this->_socketInGame->sendToSocket(this->_idSocketRoom, (void *)&value, strlen("5"));
		_sound->stopMusic("shoot");
	}
}