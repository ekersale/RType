#include "Ammo-Player.h"

AmmoPlayer::AmmoPlayer()
{
	_direction = true;
}

AmmoPlayer::~AmmoPlayer()
{
}

DRect		AmmoPlayer::calcPos(DRect pos)
{
	pos.x += 4;
	return (pos);
}

e_type		AmmoPlayer::getType() const
{
	return (AMMO4);
}

<<<<<<< HEAD
void		AmmoPlayer::setMovement(int) {
	return;
}

=======
>>>>>>> b8846131a8028feeb4d1ccee3bb64ee4587582e1
int			AmmoPlayer::getPower() const
{
	return (100);
}

#ifdef _WIN32
extern "C"
__declspec(dllexport) IAmmo* __cdecl getPtr()
{
	IAmmo *tmp = new AmmoPlayer();

	return (tmp);
}
#else
extern "C"
{
	IAmmo* getPtr()
	{
		IAmmo *tmp = new AmmoPlayer();

		return (tmp);
	}
}
#endif
