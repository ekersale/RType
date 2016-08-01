#include "MTime.hh"

#ifdef _WIN32
MTime::MTime(FILETIME ftime) : _ftime(ftime)
{

}

double MTime::getTime(ULARGE_INTEGER tbegin)
{
	double exec = 0;
	static int i = 0;

	if (i == 0) {
		tend = tbegin;
		i++;
		return (0);
	}
	exec = ((double)((tbegin.QuadPart - tend.QuadPart) / 10000)) / 1000.;
	tend = tbegin;
	return (exec);
}

void MTime::updateClock(ULARGE_INTEGER *tbegin)
{
	::GetSystemTimeAsFileTime(&_ftime);
	(*tbegin).HighPart = _ftime.dwHighDateTime;
	(*tbegin).LowPart = _ftime.dwLowDateTime;
}

#else
MTime::MTime()
{
	gettimeofday(&start, NULL);
}

double MTime::getTime()
{
	double exec = 0;

	gettimeofday(&end, NULL);
	exec = ((double)(1000 * (end.tv_sec - start.tv_sec) + ((end.tv_usec - start.tv_usec) / 1000))) / 1000.;
	start = end;
	return (exec);
}
#endif

MTime::~MTime() {
}
