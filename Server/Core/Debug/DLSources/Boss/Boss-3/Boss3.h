#ifndef BOSS3_H_
#define BOSS3_H_

#include "IEntities.h"

class Boss3 : public IEntities
{
public:
	Boss3();
	~Boss3();
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
