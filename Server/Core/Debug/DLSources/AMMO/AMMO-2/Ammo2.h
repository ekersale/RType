#ifndef AMMO2_H_
#define AMMO2_H_

#include "IAmmo.h"

class Ammo2 : public IAmmo
{
public:
	Ammo2();
	~Ammo2();
	DRect calcPos(DRect);
	e_type getType() const;
	int getPower() const;
	void setMovement(int);
private:
	int _movement;
};

#endif