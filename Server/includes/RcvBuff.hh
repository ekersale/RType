/*
* Project : R-Type
* Part : Server
* Author : giraud_d
 */

#ifndef             RCVBUFF_HH
#define             RCVBUFF_HH

#include            "Thread.hh"
#include            "ThreadPool.hh"
// Room.hh include string
#include            "Room.hh"
#include "Core.hh"

class               RcvBuff : public Thread
{
public:
    RcvBuff();
    ~RcvBuff();
    char     *get_buff(void);
    void            newClientJoinRoom(void);
    void            fillBuff(char &, saddrin &, int &);
    void            loopRcv(void);
    bool            initRcv(void *arg);
    void            runCode(void *);
private:
    Room            *_room;
    char            _buff[5];
	char			*_buffSend;
    Mutex           *_buffMutex;
    Network         *_roomNetwork;
};

#endif
