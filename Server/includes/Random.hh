#ifndef _RANDOM_HH__
# define _RANDOM_HH__

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Elems.hh"


class Random
{
public:
	Random();
	~Random();

	bool init();
	void randPos();
	Rect getPos() const;
	void setIntervalsX(int, int);
	void setIntervalsY(int, int);
	int getValueX() const;
	int getValueY() const;

private:
	Rect _pos;
	int _x0;
	int _x1;
	int _y0;
	int _y1;
};

#endif // !_RANDOM_HH__
