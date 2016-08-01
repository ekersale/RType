#ifndef BOSS1_H_
#define BOSS1_H_

#include "IEntities.h"

class Boss1 : public IEntities
{
public:
	Boss1();
	~Boss1();
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
