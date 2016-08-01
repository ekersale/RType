/*
* Project : R-Type
* Part : Server
* Author : giraud_d
 */

#include        "RcvBuff.hh"

RcvBuff::RcvBuff() {
	_buffMutex = new Mutex();
	_buffSend = (char *)malloc(5);
}

RcvBuff::~RcvBuff() {
	free(_buffSend);
	delete(_buffMutex); // Si �a beug virer �a
}

char     *RcvBuff::get_buff(void)
{
	_buffMutex->trylockSleep();

	for (int i = 0; i < 5; i++) {
		_buffSend[i] = _buff[i];
	} // Joli tek1 style

	for (int i = 1; i < 5; i++) {
        //std::cout << "Buff [" << i << "] = " << "| " << _buff[i] << " |" <<  std::endl;
		_buff[i] = 0;
	}
	_buffMutex->unlock();
    return (_buffSend);
}

void            RcvBuff::newClientJoinRoom(void) {
	_buffMutex->trylockSleep();
    _buff[0]++;
	_buffMutex->unlock();
}

void            RcvBuff::fillBuff(char &val, saddrin &requestAddr, int &idSocketClient)
{
    int                                     pos;
    std::vector<ClientInfo *>               whiteList;
    std::vector<ClientInfo *>::iterator     itWhiteList;

    pos = 1;
    whiteList = _room->get_whiteList();
    for (itWhiteList = whiteList.begin(); itWhiteList != whiteList.end(); itWhiteList++) {
       /* if ((memcmp((*itWhiteList)->get_info(), requestAddr, sizeof(saddrin)) ) == 0) {
            if (_buff[pos] == 0) // Add this check to prevent multi touch send during one turn from a client
                _buff[pos] = val;
            return ;
        }*/
        pos++;
    }
    std::cout << "Fail de la white List\n";
}

void            RcvBuff::loopRcv(void)
{
    int         idClientSocket;

    while (_room) {
        if ((idClientSocket = _roomNetwork->recvFromSocket()) > 0) {
           _buffMutex->trylockSleep();
		   if (idClientSocket < 5) // pb s�cu si co externe
		   {
			   if (_buff[idClientSocket] == 0)// Add this check to prevent multi touch send during one turn from a client
				   _buff[idClientSocket] = _roomNetwork->get_buffer()[0];
		   }
          _buffMutex->unlock();
        } else {
            std::cout << "Putain !\tThis is the end of the world as we know it" << std::endl;
            return ;
        }
    }
}

bool            RcvBuff::initRcv(void *arg)
{
    _room = (Room *)arg;
    _buff[0] = 1;
    for (int i = 1; i < 5; i++)
        _buff[i] = 0;
    _roomNetwork = _room->get_roomNetwork();
    return (true);
}

void            RcvBuff::runCode(void *arg)
{
    if (initRcv(arg))
        loopRcv();
}