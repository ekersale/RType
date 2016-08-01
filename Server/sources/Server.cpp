/*
* Project : R-Type
* Part : Server
* Author : giraud_d
 */

#include        "Server.hh"
#include        <sstream>
#include        <iostream> //tmp

/*
** This method is always execute in a room thread (when room is destroy)
 */
void            Server::deleteRoom(std::string name)
{
    std::map<std::string, Room *>::iterator it;
    std::vector<Client *>                   players;
    std::vector<Client *>::iterator         itPlayers;

    it = _rooms.find(name);
    if (it != _rooms.end()) {
        players = it->second->get_players();
        for (itPlayers = players.begin(); itPlayers != players.end(); itPlayers++)
            (*itPlayers)->setInGame(false);
        _rooms.erase(it);
    }
}

/*
** There 10 methods are executing in the main server thread
 */
bool            Server::treatCreateRoom(int &id, std::string &requestRoomName)
{
    roomPortPacket  packet;

    std::cout << "fct treatCreateRoom\n";
    _rooms[requestRoomName] = new Room(_clients[id], requestRoomName);
    _rooms[requestRoomName]->initNetwork(getNextPort());
    _clients[id]->setInGame(true);
    LaunchRoom *newRoom = new LaunchRoom(_rooms[requestRoomName]);
    _pool->scheduleThread(newRoom, (void *)this);
    //usleep(100000); //large TODO method to check if thread launched #PA
    packet.port = _rooms[requestRoomName]->get_port();
    _srvNetwork->sendToSocket(id, &packet, sizeof(roomPortPacket));
    _roomsMapMutex->unlock();
    return (true);
}

bool            Server::treatFullRoom(int &id)
{
    roomPortPacket  packet;

    std::cout << "fct treatFullRoom\n";
    packet.port = FULL;
    _srvNetwork->sendToSocket(id, &packet, sizeof(roomPortPacket));
    _roomsMapMutex->unlock();
	return (true);
}

bool            Server::treatJoinRoom(int &id, Room *target)
{
    roomPortPacket  packet;

    std::cout << "fct treatJoinRoom\n";
    if (!_clients[id]->getInGame()) {
        target->addNewPlayer(_clients[id]);
        target->addClientIdSocket(_clients[id]);
        _clients[id]->setInGame(true);
    }
    packet.port = target->get_port();

    _srvNetwork->sendToSocket(id, &packet, sizeof(roomPortPacket));
    _roomsMapMutex->unlock();
	return (true);
}

bool            Server::resendPongPacket(int &id)
{
    stdPacket   packet;

    std::cout << "fct resendPongPacket\n";
    packet.val = PONG;
    _srvNetwork->sendToSocket(id, &packet, sizeof(stdPacket));
    return (true);
}

bool            Server::treatRoomPacket(int &id)
{
    std::string                             requestRoomName;
    std::map<std::string, Room *>::iterator it;

    std::cout << "fct treatRoomPacket\n";
    if (_srvNetwork->get_filled() < 1 || _srvNetwork->get_filled() > sizeof(roomNamePacket))
        return (false);
    // TODO test this condition
    requestRoomName = _srvNetwork->get_buffer();
    if (_srvNetwork->get_filled(0) == 1 && requestRoomName[0] == PING) {
        return (resendPongPacket(id));
    }
    requestRoomName = _srvNetwork->get_buffer();
    std::cout << "=> " << requestRoomName << "\n";
    _roomsMapMutex->trylock();
    if ((it = _rooms.find(requestRoomName)) != _rooms.end()) {
        if (it->second->get_players().size() > 3) //0 to test full room for second
            return (treatFullRoom(id));
        else
            return (treatJoinRoom(id, it->second));
    } else {
        return (treatCreateRoom(id, requestRoomName));
    }
}

bool            Server::treatPingPacket(int &id)
{
    stdPacket   packet;

    std::cout << "fct treatPingPacket\n";
    if (_srvNetwork->get_filled() != sizeof(stdPacket))
        return (false);
    if (_srvNetwork->get_buffer()[0] != PING)
        return (false);
    _clients[id] = new Client(id, _srvNetwork->get_connected(id));
    packet.val = PONG;
    _srvNetwork->sendToSocket(id, &packet, sizeof(stdPacket));
    return (true);
}

bool            Server::treatPacket(int &id)
{
    std::cout << "fct TreatPacket : Hello Id : " << id << std::endl;
    if (_clients.find(id) == _clients.end()) {
        return (treatPingPacket(id));
    } else {
        return (treatRoomPacket(id));
    }
}

bool            Server::loopServer()
{
    int         idClientSocket;

    while (1) {
        std::cout << "fct loopServer\n";
        idClientSocket = _srvNetwork->recvFromSocket();
        std::cout << "new USER dbg: " << idClientSocket << std::endl;
	std::cout << "[" << _srvNetwork->get_buffer() << "]" << std::endl;
        treatPacket(idClientSocket);
    }
}

bool            Server::initServer(void *sPool)
{
    _pool = reinterpret_cast<ThreadPool *>(sPool); //la ThreadPool est recue en paramètre dans cette fonction
    _srvNetwork = new Network(AF_INET, SOCK_DGRAM, "UDP", sizeof(roomNamePacket)); // ce sizeof car c'ets la taille max d'un packet que le serveur peux recevoir
    _srvNetwork->bindSocket(PORT);
    _roomsMapMutex = new Mutex();
    std::istringstream(PORT) >> _port;
    return (true);
}

void            Server::runCode(void * sPool)
{
    if (!initServer(sPool) || !loopServer())
        return ;
}

/*
** Basic Constructor and destructor
 */
Server::Server(void) : Thread() {
};

Server::~Server(void) {
};

/*
** This method increment the port at the creation of each room
 */
int             &Server::getNextPort(void) {
    return (++_port);
}

/*
** Two useful getters called by LaunchRoom to manipulate Mutex and ThreadPool
 */
Mutex           *&Server::getRoomsMapMutex(void) {
    return (_roomsMapMutex);
}

ThreadPool      *&Server::get_pool(void) {
    return (_pool);
}
