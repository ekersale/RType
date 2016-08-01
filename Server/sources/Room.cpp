/*
* Project : R-Type
* Part : Server
* Author : giraud_d
 */

// RcvBuff.hh include Room.hh
#include                "RcvBuff.hh"
#include			"Core.hh"
#include                <sstream>

Room::Room() : _name("") {
}

Room::Room(Client *first, std::string &name) {
    _name = name;
    _players.push_back(first);
}

Room::~Room() {
}

void                        Room::addClientIdSocket(Client *client) {
    std::stringstream       ss;
    std::string             stringPort;
    int                     newIdSocket;

    ss << _port;
    stringPort = ss.str();
    newIdSocket = _roomNetwork->connectToSocket(inet_ntoa(client->get_clientInfo()->get_info().sin_addr), stringPort.c_str());
    std::cout << "The IP is : " << inet_ntoa(client->get_clientInfo()->get_info().sin_addr) << " and the port is : " << stringPort.c_str() << std::endl;
    _idSocketClients.push_back(newIdSocket);
    _whiteList.push_back((ClientInfo *)memcpy(new ClientInfo, _roomNetwork->get_connected(newIdSocket), sizeof(ClientInfo)));
}

std::vector<Client *>       Room::get_players() const {
    return _players;
}

void                        Room::addNewPlayer(Client *new_player) {
    _players.push_back(new_player);
    _rcvBuff->newClientJoinRoom();
}

std::string                 Room::get_name() const {
    return _name;
}

int                         Room::get_port(void) const {
    return (_port);
}

Network                     *Room::get_roomNetwork() const {
    return (_roomNetwork);
}

void                        Room::set_rcvBuff(RcvBuff *rcvBuff) {
    _rcvBuff = rcvBuff;
}

#include <iostream> //tmp

void                        Room::roomLoop() {
	Core *core = new Core(this);
	if (core->loadRoom() == false) {
        std::cout << "\tloadRoom Fail\n";
        return;
    }
	core->launchGame();
    std::cout << "Inside roomLoop [Room " << _name << "]\n";
}

bool                        Room::initNetwork(int &port)
{
    std::stringstream       ss;
    std::string             stringPort;

    ss << port;
    stringPort = ss.str();
    _roomNetwork = new Network(AF_INET, SOCK_DGRAM, "UDP", 512);
    _roomNetwork->bindSocket(stringPort.c_str());
    _port = port;
    addClientIdSocket(_players.front());
    return (true);
}
