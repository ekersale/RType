#ifndef MONSTER3_H_
#define MONSTER3_H_

#include "IEntities.h"

class Monster3 : public IEntities
{
public:
	Monster3();
	~Monster3();
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
