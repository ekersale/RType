/*
* Project : R-Type
* Part : Server
* Author : giraud_d
 */

#include    "Client.hh"

Client::Client(int idSocketServer, ClientInfo *clientInfo) : _idSocketServer(idSocketServer), _inGame(false), _clientInfo(clientInfo) {}

Client::~Client() {}

bool        &Client::getInGame(void) {
    return (_inGame);
}

void        Client::setInGame(bool inGame) {
    _inGame = inGame;
}

ClientInfo  *Client::get_clientInfo(void) {
    return (_clientInfo);
}

void        Client::set_clientInfo(ClientInfo *&clientInfo) {
    _clientInfo = clientInfo;
}