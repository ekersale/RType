#ifndef AMMO1_H_
#define AMMO1_H_

#include "IAmmo.h"

class Ammo1 : public IAmmo
{
public:
	Ammo1();
	~Ammo1();
	DRect calcPos(DRect);
	e_type getType() const;
	int getPower() const;
	void setMovement(int);
private:
	int _movement;
};

#endif