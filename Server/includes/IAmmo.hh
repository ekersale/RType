#ifndef _IAMMO_HH__
# define _IAMMO_HH__

#include "Elems.hh"

class IAmmo
{
public:
	virtual DRect calcPos(DRect) = 0;
	virtual e_type getType() const = 0;
	virtual int getPower() const = 0;
	virtual void setMovement(int) = 0;
};

#endif // !_IAMMO_HH__
