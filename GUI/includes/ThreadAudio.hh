#ifndef __THREADAUDIO_HH__
#define __THREADAUDIO_HH__

#include "Thread.hh"

class ThreadAudio : public Thread
{
public:
	ThreadAudio();
	~ThreadAudio();
	void runCode(void *params);
};

#endif