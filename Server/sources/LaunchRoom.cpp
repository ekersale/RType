/*
* Project : R-Type
* Part : Server
* Author : giraud_d
 */

#include            "Server.hh"
#include            <iostream> // tmp

LaunchRoom::LaunchRoom() : _room(NULL) {
}

LaunchRoom::LaunchRoom(Room *room) : _room(room) {
}

LaunchRoom::~LaunchRoom() {
}

/*
* This method init :
* - RcvBuff Object
* - Link Room and RcvBuff
* - RcvBuff Thread
* - Launch roomLoop
* This method delete :
* - RcvBuff Thread
* - RcvBuff Object
* - call deleteRoom (Server method)
* - Room Object
 */
void                LaunchRoom::runCode(void *arg)
{
    Server          *srv;
    RcvBuff         *rcvBuff;
    int             idThread;

    srv = (Server *)arg;
    std::cout << "Inside runCode [LaunchRoom]\n";
    if (_room) {
        rcvBuff = new RcvBuff();
        _room->set_rcvBuff(rcvBuff);
        if ((idThread = srv->get_pool()->scheduleThread(rcvBuff, (void *) _room)) >= 0) {
            _room->roomLoop();
            _room->get_roomNetwork()->sendToSocket(0, (void *)"", 0);
            //srv->get_pool()->endThread(idThread);
        }
        delete (rcvBuff);
        srv->getRoomsMapMutex()->trylock();
        srv->deleteRoom(_room->get_name());
        srv->getRoomsMapMutex()->unlock();
        delete (_room);
    }
}