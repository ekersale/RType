#ifndef _ELEMS_HH__
# define _ELEMS_HH__

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

typedef enum { MOB, AMMO } e_otype;


typedef struct s_struct
{
	int x;
	int y;
}				Rect;

typedef struct s_dstruct
{
	double x;
	double y;
}				DRect;

typedef struct s_stage
{
	int type;
	int number;
} t_stage;

typedef struct		s_send
{
	unsigned int	id;
	char			type;
	char			alive;
	unsigned int	pos[2];
	unsigned long	network[2];
}					t_send;

#endif // !_ELEMS_HH__
