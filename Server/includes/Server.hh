/*
* Project : R-Type
* Part : Server
* Author : giraud_d
 */

#ifndef                             SERVER_HH_
#define                             SERVER_HH_

#include                            "Thread.hh"
#include                            "ThreadPool.hh"
#include                            "Mutex.hh"
// Client.hh include Network.hh >
#include                            "Client.hh"
// LaunchRoom include Room.hh >
#include                            "LaunchRoom.hh"
#include                            "ProtoServer.h"
#include                            <map>
#include                            <string>


class                               Server : public Thread
{
public:
    void                            deleteRoom(std::string);
    bool                            treatCreateRoom(int &, std::string &);
    bool                            treatFullRoom(int &);
    bool                            treatJoinRoom(int &, Room *);
    bool                            resendPongPacket(int &id);
    bool                            treatRoomPacket(int &);
    bool                            treatPingPacket(int &);
    bool                            treatPacket(int &);
    bool                            loopServer(void);
    bool                            initServer(void *);
    void                            runCode(void *);
    Server();
    ~Server();
    int                             &getNextPort(void);
    Mutex                           *&getRoomsMapMutex(void);
    ThreadPool                      *&get_pool(void);
private:
    std::map<int, Client *>         _clients;
    Network                         *_srvNetwork;
    ThreadPool                      *_pool;
    std::map<std::string, Room *>   _rooms;
    Mutex                           *_roomsMapMutex;
    int                             _port;
};

#endif