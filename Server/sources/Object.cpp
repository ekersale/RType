#include "Object.hh"
#include "MTime.hh"
#include "Random.hh"

Object::Object(IEntities *obj, int id) : _obj(obj), _id(id) {
	_lifePoint = obj->getLifePoint();
	_dpos = *(obj->getSpawn());
	if (_dpos.y < 0)
		_dpos.y = rand() % 700;
	_size.x = 70;/*(int)(std::floor(obj->getSizeObj().x));*/
	_size.y = 68;/*(int)(std::floor(obj->getSizeObj().y));*/
	_obj->setMovement((rand() % 2) + 1);
	_type = obj->getType();
	_level = -1;
#ifdef _WIN32
	std::string path = "Dll/AMMO-" + std::to_string(_obj->getAmmo() - 4) + ".dll";
	_dll = new WDLLoader;
	if (_dll->openLib(path.c_str(), 0) == false)
#else
	std::string path = "So/AMMO-" + std::to_string(_obj->getAmmo() - 4) + ".so";
	_dll = new UDLLoader;
	if (_dll->openLib(path.c_str(), RTLD_LAZY) == false)
#endif
		_ammo = NULL;
}

Object::Object(IAmmo *ammo) : _ammo(ammo) {
	_type = ammo->getType();
	_level = -1;
	_power = ammo->getPower();
	_size.x = 16;
	_size.y = 16;
	ammo->setMovement((rand() % 2) + 1);
}

Object::~Object() {
}

void *Object::update() {
	static bool start = false;
	static int t = 0;
	if (start == false) {
		start = true;
		return (NULL);
	}
	if (_type >= MONSTER1 && _type <= MONSTER4)
	{
		_dpos = _obj->calcPos(_dpos);
		if (_obj->getFireRate() == true) {
			IAmmo *tmp = (IAmmo *)_dll->loadSym();
			IObject *ammo = new Object(tmp);
			DRect ptmp = _dpos;
			ptmp.y += 20;
			ptmp = tmp->calcPos(ptmp);
			ammo->setDRect(ptmp);
			ammo->setBelongsTo(1);
			return (ammo);
		}
	}
	else {
		_dpos = _ammo->calcPos(_dpos);
		_dpos.x -= 2;
	}
	return (NULL);
}

bool Object::setLifePoint(int lost) {
	_lifePoint -= lost;
	if (_lifePoint <= 0)
		return (false);
	return (true);
}

int Object::getPower() const {
	if (_ammo != NULL)
		return (_ammo->getPower());
	return (0);
}

void Object::setPower(const int &Power){
	_power = Power;
}

int Object::getLifePoint() const {
	return (_lifePoint);
}

Rect Object::getSizeObj() const{
	return (_size);
}

e_type Object::getType() const {
	return (_type);
}

Rect Object::getPos() {
	_pos.x = ((int)std::floor(_dpos.x));
	_pos.y = ((int)std::floor(_dpos.y));
	return (_pos);
}

int Object::getReward() const {
	return (_obj->getReward());
}

int Object::getLevel() const {
	return (_level);
}

int Object::getId() const {
	return (_id);
}

void Object::setId(const int &id){
	_id = id;
}

void Object::setDRect(const DRect &rec) {
	_dpos = rec;
}

void Object::setBelongsTo(const int &v) {
	_belongs = v;
}

bool Object::getBelongsTo() const {
	return (_belongs);
}
