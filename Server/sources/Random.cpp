#include "Random.hh"

Random::Random()
{
	_pos.x = 0;
	_pos.y = 0;
}

Random::~Random() {
}

void Random::setIntervalsX(int x, int y)
{
	_x0 = x;
	_x1 = y;
}

void Random::setIntervalsY(int x, int y)
{
	_y0 = x;
	_y1 = y;
}

bool Random::init()
{
#ifdef _WIN32
	srand((unsigned)time(NULL));
	return (true);
#else
	struct timespec       ts;

	if (clock_gettime(CLOCK_REALTIME, &ts) < 0)
		return (false);
	srand(ts.tv_nsec);
#endif
}

void Random::randPos()
{
	_pos.x = _x0 + (rand() % _x1);
	_pos.y = _y0 + (rand() % _y1);
}

Rect Random::getPos() const
{
	return (_pos);
}

int Random::getValueX() const
{
	return (_pos.x);
}

int Random::getValueY() const
{
	return (_pos.y);
}