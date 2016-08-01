#ifndef THREADS_TEST_HH_
#define THREADS_TEST_HH_

#include	<vector>

#include "Thread.hh"
#include "ThreadPool.hh"

#include "CoreGame.hh"
#include "CoreAction.hh"

#include <stdio.h>



class HandlePool : public Thread
{
public:
	HandlePool(void);
	~HandlePool(void);
	void runCode(void * handlePool);
	bool	ping(Network *senderclt, int idSocketServer);
	bool	receivePort(Network *senderclt, int idSocketServer);
	

	//Getters
	Window			*getWindow(void) const;
	Sound			*getSound(void) const;
	ThreadPool		*getThreadPool(void) const;
	CoreAction		*getThreadReception(void) const;
	CoreGame		*getThreadGui(void) const;

	Network			*getSocketPingServer(void) const;
	Network			*getSocketInGame(void) const;
	Shared			*getClassShared(void) const;

	int				getPortRoom(void) const;
	int				getIdSocketServer(void) const;
	int				getIdSocketRoom(void) const;

private:
	Window				*_window;
	Sound				*_sound;
	ThreadPool			*_threadPool;
	CoreAction			*_threadReception;
	CoreGame			*_threadGui;
	Network				*_socketPingServer;
	Network				*_socketInGame;
	Shared				*_classShared;

	int					_idSocketServer;
	int					_idSocketRoom;
};

#endif