#ifndef IAMMO_H_
#define IAMMO_H_

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

class IAmmo
{
public:
	virtual DRect calcPos(DRect) = 0;
	virtual e_type getType() const = 0;
	virtual int getPower() const = 0;
<<<<<<< HEAD
	virtual void setMovement(int) = 0;
=======
>>>>>>> b8846131a8028feeb4d1ccee3bb64ee4587582e1
};

#endif