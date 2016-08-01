#ifndef MONSTER2_H_
#define MONSTER2_H_

#include "IEntities.h"

class Monster2 : public IEntities
{
public:
	Monster2();
	~Monster2();
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
	bool _direction;
};

#endif
