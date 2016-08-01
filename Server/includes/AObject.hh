#ifndef _AOBJECT_HH__
# define _AOBJECT_HH__

#include "IObject.hh"

class AObject :  public IObject
{
public:
	virtual void init() = 0;
	virtual void update() = 0;
	Rect getPos() { return _pos;  };
	int getType() { return _type; };
	int getLevel() { return _level; };

protected:
	Rect _pos;
	int _type;
	int _level;
	int _hp;
	/*Sauvegarde du temps de la création*/
};

#endif // !_AOBJECT_HH__