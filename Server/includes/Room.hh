/*
* Project : R-Type
* Part : Server
* Author : giraud_d
 */

#ifndef                             ROOM_HH
#define                             ROOM_HH

#include                            "Client.hh"
#include                            "Network.hh"
//#include							"Core.hh"
#include                            <vector>
#include                            <string>

class                               RcvBuff;
class Core;

class                               Room
{
public:
    Room();
    Room(Client *, std::string &);
    ~Room();
    void                            addClientIdSocket(Client *);
    std::vector<Client *>           get_players() const;
    void                            addNewPlayer(Client *);
    void                            roomLoop();
    std::string                     get_name() const;
    int                             get_port() const;
    Network                         *get_roomNetwork() const;
    void                            set_rcvBuff(RcvBuff *);
    bool                            initNetwork(int &);
	RcvBuff							*getRcvBuff() const { return _rcvBuff; }
	Network							*getNetwork() const { return _roomNetwork; }
	std::vector<int>				&get_idSocketClients() { return _idSocketClients; }
    std::vector<ClientInfo *>       get_whiteList() { return _whiteList; }

private:
    std::vector<ClientInfo *>       _whiteList;
    std::string                     _name;
    std::vector<Client *>           _players;
    int                             _port;
    Network                         *_roomNetwork;
    RcvBuff                         *_rcvBuff;
	std::vector<int>				_idSocketClients;
};

#endif