#ifndef AMMOPLAYER_H_
#define AMMOPLAYER_H_

#include "IAmmo.h"

class AmmoPlayer : public IAmmo
{
public:
	AmmoPlayer();
	~AmmoPlayer();
	DRect calcPos(DRect);
	e_type getType() const;
	int getPower() const;
<<<<<<< HEAD
	void setMovement(int);

=======
>>>>>>> b8846131a8028feeb4d1ccee3bb64ee4587582e1
private:
	double _direction;
};

#endif