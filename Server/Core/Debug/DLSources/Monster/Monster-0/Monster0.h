#ifndef MONSTER0_H_
#define MONSTER0_H_

#include "IEntities.h"

class Monster0 : public IEntities
{
public:
	Monster0();
	~Monster0();
	DRect calcPos(DRect);
	int getLifePoint() const;
	DRect *getSpawn() const;
	DRect getSizeObj() const;
	e_type getType() const;
	bool getFireRate() const;
	e_type getAmmo() const;
	int getReward() const;
	void setMovement(int);
private:
	int _movement;
};

#endif
