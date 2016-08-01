#ifndef BOSS2_H_
#define BOSS2_H_

#include "IEntities.h"

class Boss2 : public IEntities
{
public:
	Boss2();
	~Boss2();
	DRect calcPos(DRect);
	int getLifePoint() const;
	DRect *getSpawn() const;
	DRect getSizeObj() const;
	e_type getType() const;
	bool getFireRate() const;
	e_type getAmmo() const;
	int getReward() const;

private:
	double _angle;
};

#endif
