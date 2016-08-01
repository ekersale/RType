#ifndef COMMANDERTEST_H_
#define COMMANDERTEST_H_

#include "IEntities.h"

class CommanderTest : public IEntities
{
public:
	CommanderTest();
	~CommanderTest();
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