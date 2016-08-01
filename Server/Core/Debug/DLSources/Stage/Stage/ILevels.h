#ifndef ILEVELS_H_
#define ILEVELS_H_

#include <vector>

typedef struct s_stage {
	int type;
	int number;
} t_stage;

typedef enum {
	CLIENT = 0,
	IP = 1,
	CO = 2,
	END = 3,
	PLAYER = 4,
	AMMO1 = 5,
	AMMO2 = 6,
	MONSTER1 = 7,
	MONSTER2 = 8,
	MONSTER3 = 9,
	MONSTER4 = 10,
	BOSS1 = 11,
	BOSS2 = 12,
	BOSS3 = 13
} e_type;

class ILevels
{
public:
	virtual std::vector<std::vector<std::vector<t_stage *> > > getStages() = 0;
};

#endif // !ILEVELS_H_
