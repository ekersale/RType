/*
* Project : R-Type
* Part : Server
* Author : giraud_d
 */

#ifndef             LAUNCHROOM_HH
#define             LAUNCHROOM_HH

#include            "Thread.hh"
#include            "ThreadPool.hh"
#include            "Room.hh"
#include            "RcvBuff.hh"

class               LaunchRoom : public Thread
{
public:
    LaunchRoom();
    LaunchRoom(Room *);
    ~LaunchRoom();
    void            runCode(void *);
private:
    Room            *_room;
};

#endif