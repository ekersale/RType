#ifndef _MTIME_HH__
# define _MTIME_HH__

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif
#include <ctime>

class MTime
{
public:
#ifdef _WIN32
	MTime(FILETIME);
#else
	MTime();
#endif
	~MTime();

#ifdef _WIN32
	double getTime(ULARGE_INTEGER);
	void updateClock(ULARGE_INTEGER *);
#else
	double getTime();
#endif
private:
#ifdef _WIN32
	FILETIME _ftime;
	ULARGE_INTEGER tend;
#else
	struct timeval end;
	struct timeval start;
#endif
};

#endif // !_MTIME_HH__
