#include "Core.hh"

Core::Core()
{
	_isAlive = true;
	_id = 0;
}

Core::~Core()
{
}

bool Core::loadRoom()
{
	dll = new WDLLoader;
	if (dll->openLib("Dll/Stage.dll", 0) == false)
		return (false);
	levels = (ILevels *)dll->loadSym();
	stage = new Stage(levels);
	return (true);
}

bool Core::checkCollision(IObject *obj) {
	for (std::vector<IObject *>::iterator it = _vobj->begin(); it != _vobj->end(); ++it) {
		IObject *tmp = (Object *)(*it);
		if ((obj->getType() >= MONSTER1) && (tmp->getType() < MONSTER1)) {
			// check la position des deux // empèche la collision entre deux mobs
		}
	}
	return (true);
}

void Core::checkPosition() {
	for (std::vector<IObject *>::iterator it = _vobj->begin(); it != _vobj->end(); ++it) {
		IObject *tmp = (Object *)(*it);
		if (tmp->getPos().x < (0 - tmp->getSizeObj().x)) {
			_vobj->erase(it);
			checkPosition();
		}
	}
}

bool Core::launchLevel()
{
	/*#ifdef _WIN32
	FILETIME	_ttmp;
	MTime		*_mtime;
	ULARGE_INTEGER tbegin;
	#endif*/
	while (_isAlive == true && _vobj->size() > 0) {
		Sleep(30);
		std::vector<IObject *> vtmp;
		for (std::vector<IObject *>::iterator it = _vobj->begin(); it != _vobj->end(); ++it) {
			IObject * tmp = (Object *)((*it)->update());
			if (tmp != NULL) {
				tmp->setId(_id);
				_id++;
				vtmp.push_back(tmp);
			}
			checkCollision((Object *)*it);
			checkPosition();
		}
		while (!vtmp.empty()) {
			_vobj->push_back(vtmp.back());
			vtmp.pop_back();
		}
		
	}
	return (true);
}

void Core::launchGame()
{
	bool _fin = false;
	int lvl = 1;
	while (!_fin || ++lvl <= stage->getStageNumber()) {
		stage->setLvlStage(lvl);
		std::vector<t_stage *> *tmp;
		_id = 0;
		if ((tmp = stage->getWave()) == NULL)
			_fin = true;
		else
		{
			_vobj = new std::vector<IObject *>;
			while (tmp->empty() != true)
			{
				t_stage *mobs = tmp->back();
				tmp->pop_back();
				IDLLoader *dll = new WDLLoader;
				std::string name = "./Dll/Monster-";
				name += std::to_string(mobs->type - MONSTER1 + 1);
				name += ".dll";
				if (dll->openLib(name.c_str(), 0) != false) {
					IEntities *entities = (IEntities *)dll->loadSym();
					for (int i = 0; i < mobs->number; ++i) {
						_vobj->push_back(new Object(entities, _id));
						_id++;
					}
				}
			}
			if (launchLevel() == false)
				return;
		}
	}
}