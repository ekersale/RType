/*
* Project : R-Type
* Part : Server
* Author : giraud_d
 */

#ifndef             CLIENT_HH
#define             CLIENT_HH

#include            "Network.hh"

class               Client
{
public:
    Client(int, ClientInfo *);
    ~Client();
    bool            &getInGame(void);
    void            setInGame(bool);
    ClientInfo      *get_clientInfo(void);
    void            set_clientInfo(ClientInfo *&);
private:
    int             _idSocketServer;
    bool            _inGame;
    ClientInfo      *_clientInfo;
};

#endif