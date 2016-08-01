#ifndef AMMO3_H_
#define AMMO3_H_

#include "IAmmo.h"

class Ammo3 : public IAmmo
{
public:
	Ammo3();
	~Ammo3();
	DRect calcPos(DRect);
	e_type getType() const;
	int getPower() const;
	void setMovement(int);
private:
	int _movement;
	bool _direction;
};

#endif