#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif
#include <ctime>
#include <math.h>
#include <iostream>

typedef struct s_dstruct
{
	double x;
	double y;
}				DRect;

typedef enum {
	CLIENT = 0,
	IP = 1,
	CO = 2,
	END = 3,
	PLAYER = 4,
	AMMO1 = 5,
	AMMO2 = 6,
	AMMO3 = 7,
	AMMO4 = 8,
	MONSTER1 = 9,
	MONSTER2 = 10,
	MONSTER3 = 11,
	MONSTER4 = 12,
	BOSS1 = 13,
	BOSS2 = 14,
	BOSS3 = 15
} e_type;

class IEntities
{
public:
	virtual DRect calcPos(DRect) = 0;
	virtual int getLifePoint() const = 0;
	virtual DRect *getSpawn() const = 0;
	virtual DRect getSizeObj() const = 0;
	virtual e_type getType() const = 0;
	virtual bool getFireRate() const = 0;
	virtual e_type getAmmo() const = 0;
	virtual int getReward() const = 0;
};

