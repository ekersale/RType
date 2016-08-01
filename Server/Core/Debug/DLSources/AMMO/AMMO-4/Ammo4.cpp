#include "Ammo4.h"
# define M_PI           3.14159265358979323846
#define RADIANS(x)		(x*(M_PI/180))

Ammo4::Ammo4()
{
	_movement = 0;
	_direction = true;
	_angle = 0.0;
}

Ammo4::~Ammo4()
{
}

void		Ammo4::setMovement(int move)
{
	(void)move;
}

DRect		Ammo4::calcPos(DRect pos)
{
	DRect tmp;

	tmp.x = pos.x - 2;
	tmp.y = (pos.y + 10 * (double)(cos(RADIANS(_angle))));
	_angle += 0.9;
	return (tmp);
}

e_type		Ammo4::getType() const
{
	return (AMMO4);
}

int			Ammo4::getPower() const
{
	return (100);
}

#ifdef _WIN32
extern "C"
__declspec(dllexport) IAmmo* __cdecl getPtr()
{
	IAmmo *tmp = new Ammo4();

	return (tmp);
}
#else
extern "C"
{
  IAmmo* getPtr()
  {
    IAmmo *tmp = new Ammo4();

    return (tmp);
  }
}
#endif