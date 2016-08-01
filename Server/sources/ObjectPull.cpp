#include "ObjectPull.hh"

ObjectPull::ObjectPull(std::vector<t_stage *> *stage) : _stage(stage) {
	_obj = new std::vector<IObject *>;
	_id = 0;
}

ObjectPull::~ObjectPull()
{
}

void ObjectPull::createObj()
{
	while (!_stage->empty())
	{
		t_stage *tmp = _stage->back();
		_stage->pop_back();
		for (int n = 0; n < tmp->number; n++) {
#ifdef _WIN32
			IDLLoader *dll = new WDLLoader;
#else
			IDLLoader *dll = new UDLLoader;
#endif
			std::string stmp = "Monster-";
			stmp += std::to_string(_id);
			dll->openLib(stmp.c_str(), 0);
			IEntities *tmp = (IEntities *)dll->loadSym();
			IObject *obj = new Object(tmp, _id);
			_id++;
			_obj->push_back(obj);
		}
	}
}

std::vector<IObject *> *ObjectPull::getObjs() const
{
	return (_obj);
}