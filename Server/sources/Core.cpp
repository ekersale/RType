#include	"RcvBuff.hh"

Core::Core(Room *room) : _room(room)
{
	_room->get_name();
	_isAlive = true;
	_id = 0;
	_score = 0;
	mapPtr[0] = &Core::PlayerInactive;
	mapPtr[1] = &Core::PlayerLeft;
	mapPtr[2] = &Core::PlayerRight;
	mapPtr[3] = &Core::PlayerUp;
	mapPtr[4] = &Core::PlayerDown;
	mapPtr[5] = &Core::PlayerFire;
}

Core::~Core()
{
}

bool Core::loadRoom()
{
#ifdef _WIN32
	dll = new WDLLoader;
	if (dll->openLib("Dll/Stage.dll", 0) == false)
#else
	dll = new UDLLoader;
	if (dll->openLib("So/Stage.so", RTLD_LAZY) == false)
#endif
		return (false);
	levels = (ILevels *)dll->loadSym();
	if (levels == NULL)
		std::cerr << "Level is null." << std::endl;
	stage = new Stage(levels);
	return (true);
}

bool Core::valueInRange(int value, int min, int max)
{
	return (value >= min) && (value <= max);
}

bool Core::rectOverlap(IObject *A, IObject *B)
{
	bool xOverlap = valueInRange(A->getPos().x, B->getPos().x, B->getPos().x + B->getSizeObj().x) ||
		valueInRange(B->getPos().x, A->getPos().x, A->getPos().x + A->getSizeObj().x);
	bool yOverlap = valueInRange(A->getPos().y, B->getPos().y, B->getPos().y + B->getSizeObj().y) ||
		valueInRange(B->getPos().y, A->getPos().y, A->getPos().y + A->getSizeObj().y);
	return (xOverlap && yOverlap);
}

bool Core::rectOverlap(Player *A, IObject *B)
{
	bool xOverlap = valueInRange(A->getPos().x, B->getPos().x, B->getPos().x + B->getSizeObj().x) ||
		valueInRange(B->getPos().x, A->getPos().x, A->getPos().x + A->getSizeObj().x);
	bool yOverlap = valueInRange(A->getPos().y, B->getPos().y, B->getPos().y + B->getSizeObj().y) ||
		valueInRange(B->getPos().y, A->getPos().y, A->getPos().y + A->getSizeObj().y);
	return (xOverlap && yOverlap);
}

IObject *Core::checkCollision(IObject *obj) {
	for (std::vector<IObject *>::iterator it = _vobj->begin(); it != _vobj->end(); ++it) {
		IObject *tmp = (Object *)(*it);
		if (tmp != obj) {
			if ((obj->getType() >= MONSTER1) && (tmp->getType() < MONSTER1) && tmp->getBelongsTo() == 0) {
				if (rectOverlap(obj, tmp) == true) {
					if (obj->getType() >= MONSTER1 && obj->getType() <= MONSTER4) {
						obj->setLifePoint(tmp->getPower());
						return (tmp);
					}
					else {
						tmp->setLifePoint(obj->getPower());
						return (obj);
					}
				}
			}
		}
	}
	return (NULL);
}

IObject *Core::checkCollision(Player *player) {
	if (player->getLifePoint() <= 0)
		return (NULL);
	for (std::vector<IObject *>::iterator it = _vobj->begin(); it != _vobj->end(); ++it) {
		IObject *tmp = (Object *)(*it);
		if (tmp->getType() < MONSTER1 && tmp->getBelongsTo() == 1) {
			if (rectOverlap(player, tmp) == true) {
				if (tmp->getType() <= MONSTER1) {
					player->setLifePoint(tmp->getPower());
					return (tmp);
				}
			}
		}
	}
	return (NULL);
}

bool Core::checkPosition() {
	for (std::vector<IObject *>::iterator it = _vobj->begin(); it != _vobj->end(); ++it) {
		IObject *tmp = (Object *)(*it);
		if (tmp->getPos().x < (0 - tmp->getSizeObj().x) && tmp->getType() >= MONSTER1 && tmp->getType() <= MONSTER4) {
			_vobj->erase(it);
			return (false);
		}
		if ((tmp->getPos().x < (0 - tmp->getSizeObj().x) || tmp->getPos().y < (0 - tmp->getSizeObj().y) ||
			tmp->getPos().y >(720 + tmp->getSizeObj().y)) && (tmp->getType() >= AMMO1 && tmp->getType() <= AMMO4)) {
			_vobj->erase(it);
			return (false);
		}
	}
	return (true);
}

void Core::PlayerInactive(int id) {
	return;
}

void Core::PlayerFire(int id) {
	IObject *tmp = (Object *)_players[id]->newFire();
	if (tmp != NULL) {
		tmp->setId(_id);
		_id++;
		_vobj->push_back(tmp);
		sendUpdates(tmp);
	}
	else
		std::cerr << "error : player's ammo dll not loaded" << std::endl;
}

#define			MAX_X	1210		//1277
#define			MAX_Y	665		//717
#define			MIN_X	3
#define			MIN_Y	3

void Core::PlayerLeft(int id) {
	if (_players.find(id) != _players.end()) {
		Rect tmp = _players[id]->getPos();
		if (tmp.x > MIN_X)
			tmp.x -= 6;
		_players[id]->setPos(tmp);
		sendUpdates(_players[id]);
	}
}

void Core::PlayerRight(int id) {
	if (_players.find(id) != _players.end()) {
		Rect tmp = _players[id]->getPos();
		if (tmp.x < MAX_X)
			tmp.x += 6;
		_players[id]->setPos(tmp);
		sendUpdates(_players[id]);
	}
}

void Core::PlayerUp(int id) {
	if (_players.find(id) != _players.end()) {
		Rect tmp = _players[id]->getPos();
		if (tmp.y > MIN_Y)
			tmp.y -= 6;
		_players[id]->setPos(tmp);
		sendUpdates(_players[id]);
	}
}

void Core::PlayerDown(int id) {
	if (_players.find(id) != _players.end()) {
		Rect tmp = _players[id]->getPos();
		if (tmp.y < MAX_Y)
			tmp.y += 6;
		_players[id]->setPos(tmp);
		sendUpdates(_players[id]);
	}
}


void Core::getPlayerEvent()
{
	char *buffEvent = _room->getRcvBuff()->get_buff();
	int tmp;
	if ((tmp = (int)buffEvent[0] - _players.size()) > 0) {
		while (tmp > 0) {
			_players[_players.size() + 1] = new Player(_players.size() + 1);
			tmp--;
			sendUpdates(_players[_players.size()]);
		}
	}
	for (int i = 1; i <= (int)buffEvent[0]; ++i) {
		//std::cout << "Buf event === " << (int)buffEvent[i] << std::endl;
		if (mapPtr.find((int)(buffEvent[i])) != mapPtr.end()) {
			(this->*mapPtr[(int)(buffEvent[i])])(i);
		}
	}
}

bool Core::sendUpdates(IObject *tmp) {
	t_send tosend;
	bool error = true;
	tosend.id = tmp->getId();
	tosend.type = tmp->getType();
	tosend.alive = 1;
	tosend.pos[0] = tmp->getPos().x;
	tosend.pos[1] = tmp->getPos().y;
	tosend.network[0] = 0;
	tosend.network[1] = 0;
	for (std::vector<int>::iterator it = _room->get_idSocketClients().begin();
		it != _room->get_idSocketClients().end(); ++it) {
		error = _room->getNetwork()->sendToSocket(*it, &tosend, sizeof(t_send));
	}
	if (error == false)
		return (false);
	return (true);
}

bool Core::sendUpdates(Player *tmp) {
	t_send tosend;
	bool error = true;
	tosend.id = tmp->getId();
	tosend.type = PLAYER;
	tosend.alive = 1;
	tosend.pos[0] = tmp->getPos().x;
	tosend.pos[1] = tmp->getPos().y;
	tosend.network[0] = 0;
	tosend.network[1] = 0;
	for (std::vector<int>::iterator it = _room->get_idSocketClients().begin();
		it != _room->get_idSocketClients().end(); ++it) {
		error = _room->getNetwork()->sendToSocket(*it, &tosend, sizeof(tosend));
	}
	if (error == false)
		return (false);
	return (true);
}

bool Core::sendEndGame() {
	t_send tosend;
	bool error = true;
	tosend.id = _score;
	tosend.type = END;
	tosend.alive = 0;
	tosend.pos[0] = 0;
	tosend.pos[1] = 0;
	tosend.network[0] = 0;
	tosend.network[1] = 0;
	for (std::vector<int>::iterator it = _room->get_idSocketClients().begin();
		it != _room->get_idSocketClients().end(); ++it) {
		error = _room->getNetwork()->sendToSocket(*it, &tosend, sizeof(tosend));
	}
	if (error == false)
		return (false);
	return (true);
}

bool Core::sendDeath(IObject *tmp) {
	t_send tosend;
	bool error = true;
	tosend.id = tmp->getId();
	tosend.type = tmp->getType();
	tosend.alive = 0;
	tosend.pos[0] = tmp->getPos().x;
	tosend.pos[1] = tmp->getPos().y;
	tosend.network[0] = 0;
	tosend.network[1] = 0;
	for (std::vector<int>::iterator it = _room->get_idSocketClients().begin();
		it != _room->get_idSocketClients().end(); ++it) {
		error = _room->getNetwork()->sendToSocket(*it, &tosend, sizeof(t_send));
	}
	if (error == false)
		return (false);
	return (true);
}

bool Core::sendDeath(Player *tmp) {
	t_send tosend;
	bool error = true;
	tosend.id = tmp->getId();
	tosend.type = PLAYER;
	tosend.alive = 0;
	tosend.pos[0] = tmp->getPos().x;
	tosend.pos[1] = tmp->getPos().y;
	tosend.network[0] = 0;
	tosend.network[1] = 0;
	for (std::vector<int>::iterator it = _room->get_idSocketClients().begin();
		it != _room->get_idSocketClients().end(); ++it) {
		error = _room->getNetwork()->sendToSocket(*it, &tosend, sizeof(tosend));
	}
	if (error == false)
		return (false);
	return (true);
}

bool Core::launchLevel()
{
	double time = 0.f;
	int mobalive = _vobj->size();
#ifdef _WIN32
	FILETIME	ttmp{ 0, 0 };
	MTime		*mtime = new MTime(ttmp);
	ULARGE_INTEGER tbegin;
#else
	MTime		*mtime = new MTime;
	struct timeval start;
#endif
	while (_isAlive == true && mobalive > 0) {
#ifdef _WIN32
		mtime->updateClock(&tbegin);
		if ((time = mtime->getTime(tbegin)) < 0.02) {
			int res = (int)std::floor((0.02 - time) * 1000);
			Sleep(res);
		}
#else
		if ((time = mtime->getTime()) < 0.02) {
			int res = (int)std::floor((0.02 - time) * 1000);
			usleep(res * 1000);
		}
#endif
		mobalive = 0;
		std::vector<IObject *> vtmp;
		std::vector<IObject *> death;
		for (std::vector<IObject *>::iterator it = _vobj->begin(); it != _vobj->end(); ++it) {
			IObject * tmp = (Object *)((*it)->update());
			if ((*it)->getType() >= MONSTER1 && (*it)->getType() <= MONSTER4 && (*it)->getLifePoint() > 0)
				mobalive++;
			if (tmp != NULL) {
				tmp->setId(_id);
				_id++;
				vtmp.push_back(tmp);
				sendUpdates(tmp);
			}
			else
				sendUpdates((IObject *)(*it));
			if ((tmp = checkCollision((Object *)*it)) != NULL) {
				if (std::find(death.begin(), death.end(), (IObject *)(*it)) == death.end())
					death.push_back(tmp);
			}
			if ((*it)->getLifePoint() < 0 && (*it)->getType() > AMMO4) {
				if (std::find(death.begin(), death.end(), (IObject *)(*it)) == death.end()) {
					death.push_back((IObject *)(*it));
					_score += (*it)->getReward();
				}
			}
		}
		while (!checkPosition());
		while (!vtmp.empty()) {
			_vobj->push_back(vtmp.back());
			vtmp.pop_back();
		}
		while (!death.empty()) {
			for (std::vector<IObject *>::iterator it = _vobj->begin(); it != _vobj->end(); ++it) {
				if ((*it) == death.back()) {
					if (it != _vobj->end())
						_vobj->erase(it);
					else
						_vobj->pop_back();
					break;
				}
			}
			sendDeath(death.back());
			death.pop_back();
		}
		for (std::map<int, Player *>::iterator it = _players.begin(); it != _players.end(); ++it) {
			IObject *tmp;
			if ((tmp = checkCollision(it->second)) != NULL) {
				if (std::find(_vobj->begin(), _vobj->end(), tmp) != _vobj->end()) {
					sendDeath(tmp);
					_vobj->erase(std::find(_vobj->begin(), _vobj->end(), tmp));
				}
			}
		}
		int stmp = _players.size();
		int count = 0;
		for (int i = 1; i <= stmp; ++i) {
			if (_players[i]->getLifePoint() <= 0) {
				sendDeath(_players[i]);
				count++;
			}
		}
		if (count == _players.size() && _players.size() > 0) {
			sendEndGame();
			return (false);
		}
		getPlayerEvent();
	}
	return (true);
}

void Core::launchGame()
{
	bool _fin = false;
	int lvl = 0;

	while (!_fin && ++lvl <= stage->getStageNumber()) {
		stage->setLvlStage(lvl);
		std::vector<t_stage *> *tmp;
		_id = 0;
		while ((tmp = stage->getWave()) != NULL)
			/*if ((tmp = stage->getWave()) == NULL)
				_fin = true;
				else*/
		{
			_vobj = new std::vector<IObject *>;
			while (tmp->empty() != true)
			{
				t_stage *mobs = tmp->back();
				tmp->pop_back();
#ifdef _WIN32
				IDLLoader *dll = new WDLLoader;
				std::string name = "./Dll/Monster-";
				name += std::to_string(mobs->type - MONSTER1 + 1);
				name += ".dll";
#else
				IDLLoader *dll = new UDLLoader;
				std::string name = "./So/Monster-";
				name += std::to_string(mobs->type - MONSTER1 + 1);
				name += ".so";
#endif
#ifdef _WIN32
				if (dll->openLib(name.c_str(), 0) != false)
#else
				if (dll->openLib(name.c_str(), RTLD_LAZY) != false)
#endif
				{
					IEntities *entities = (IEntities *)dll->loadSym();
					for (int i = 0; i < mobs->number; ++i) {
						_vobj->push_back(new Object(entities, _id));
						_id++;
					}
				}
			}
			if (launchLevel() == false) {
				std::cout << "End Game\n";
				return;
			}
		}
	}
	sendEndGame();
}
