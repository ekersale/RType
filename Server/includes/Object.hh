#ifndef _OBJECT_HH__
# define _OBJECT_HH__

#include <iostream>
#include <string>
#ifdef _WIN32
#include "WDLLoader.hh"
#else
#include "UDLLoader.hh"
#include <cmath>
#endif
#include "IEntities.hh"
#include "IObject.hh"
#include "MTime.hh"
#include "IAmmo.hh"


class Object : public IObject
{
public:
	Object(IEntities *, int);
	Object(IAmmo *);
	~Object();

	void *update();
	int getPower() const;
	void setPower(const int &);
	int getLifePoint() const;
	Rect getSizeObj() const;
	e_type getType() const;
	Rect getPos();
	int getLevel() const;
	int getId() const;
	bool setLifePoint(int);
	void setId(const int &);
	void setDRect(const DRect &);
	void setBelongsTo(const int &);
	bool getBelongsTo() const;
	int getReward() const;
	

private:
	IEntities	*_obj;
	IAmmo		*_ammo;
	int			_id;
	int			_power;
	int			_lifePoint;
	Rect		_pos;
	Rect		_size;
	DRect		_dpos;
	e_type		_type;
	int			_level;
	int			_belongs;
	IDLLoader	*_dll;
};

#endif // !_OBJECT_HH__
