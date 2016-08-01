#ifndef _PLAYER_HPP__
# define _PLAYER_HPP__

#include "IDLLoader.hh"
#include "Elems.hh"

class Player
{
public:
	Player(int id) : _id(id) {
		_life = 600; _pos.x = 10; _size.x = 64; _size.y = 47; switch (id) {
		case 1: _pos.y = 100; break; case 2: _pos.y = 300; break;
		case 3: _pos.y = 500; break; case 4: _pos.y = 700; break;
		}
#ifdef _WIN32
		std::string path = "Dll/AMMO-Player.dll";
		_dll = new WDLLoader;
		if (_dll->openLib(path.c_str(), 0) == false)
#else
		std::string path = "So/AMMO-2.so";
		_dll = new UDLLoader;
		if (_dll->openLib(path.c_str(), RTLD_LAZY) == false)
#endif
			_ammo = NULL;
	}
	~Player(){}

	int getId() const {
		return (_id);
	}

	Rect getPos() const {
		return (_pos);
	}

	void setPos(const Rect &pos) {
		_pos.x = pos.x;
		_pos.y = pos.y;
	}

	void *newFire() {
		IAmmo *tmp = (IAmmo *)_dll->loadSym();
		if (tmp == NULL)
			return (NULL);
		IObject *ammo = new Object(tmp);
		_dpos.x = (double)_pos.x + 20;
		_dpos.y = (double)_pos.y + 13;
		DRect ptmp = tmp->calcPos(_dpos);
		ammo->setDRect(ptmp);
		ammo->setBelongsTo(0);
		return (ammo);
	}

	Rect getSizeObj() const{
		return (_size);
	}

	int getLifePoint() const {
		return (_life);
	}

	void setLifePoint(const int &value) {
		_life -= value;
	}

private:
	int			_id;
	int			_life;
	Rect		_pos;
	DRect		_dpos;
	IDLLoader	*_dll;
	IAmmo		*_ammo;
	Rect		_size;
};

#endif // !_PLAYER_HPP__
