#ifndef _IENTITIES_HH__
# define _IENTITIES_HH__

#pragma once
#include "Elems.hh"

class IEntities
{
public:
	virtual DRect calcPos(DRect) = 0;
	virtual void setMovement(int) = 0;
	virtual int getLifePoint() const = 0;
	virtual DRect *getSpawn() const = 0;
	virtual DRect getSizeObj() const = 0;
	virtual e_type getType() const = 0;
	virtual bool getFireRate() const = 0;
	virtual e_type getAmmo() const = 0;
	virtual int getReward() const = 0;
};

#endif // !_IENTITIES_HH__
