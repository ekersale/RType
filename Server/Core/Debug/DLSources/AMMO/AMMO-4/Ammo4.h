#ifndef AMMO4_H_
#define AMMO4_H_

#include "IAmmo.h"
#include <cmath>
#include <iostream>

class Ammo4 : public IAmmo
{
public:
	Ammo4();
	~Ammo4();
	DRect calcPos(DRect);
	e_type getType() const;
	int getPower() const;
	void setMovement(int);
private:
	int _movement;
	bool _direction;
	double _angle;
};

#endif