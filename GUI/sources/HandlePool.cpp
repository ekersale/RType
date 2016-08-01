
#include	"HandlePool.hh"
#include	"ThreadAudio.hh"
#include	"Shared.hh"

//t_sconnect _sconnect;

HandlePool::HandlePool() : Thread()
{
	this->_window = new Window();
	this->_sound = new Sound();
	this->_socketPingServer = new Network(AF_INET, SOCK_DGRAM, "UDP", 32);
	this->_socketInGame = new Network(AF_INET, SOCK_DGRAM, "UDP", 32);
	this->_classShared = new Shared();
	this->_threadReception = new CoreAction();
	this->_threadGui = new CoreGame();

	//Affectation pour le thread Reception
	this->_threadReception->setSocketInGame(this->_socketInGame);
	this->_threadReception->setClassShared(this->_classShared);

	//Affectation pour le thread GUI
	this->_threadGui->setWindow(this->_window);
	this->_threadGui->setSound(this->_sound);
	this->_threadGui->setClassShared(this->_classShared);
	this->_threadGui->setSocketInGame(this->_socketInGame);
}

HandlePool::~HandlePool()
{

}

void	HandlePool::runCode(void *handlePool)
{	
	this->_threadPool = reinterpret_cast<ThreadPool *>(handlePool);
	this->_idSocketServer = this->_socketPingServer->connectToSocket(_sconnect.ip, _sconnect.port);

	if ((this->ping(this->_socketPingServer, this->_idSocketServer) == false))
		puts("On ne peut pas se connecter au serveur");
	else
	{
		if ((this->receivePort(this->_socketPingServer, this->_idSocketServer) == false))
			puts("On ne peut pas acceder a une room");
		else
		{
			//Lancement Thread pour la reception	
			this->_threadPool->scheduleThread(this->_threadReception, (void *)NULL);
			
			//Lancement Thread pour la GUI
			this->_threadPool->scheduleThread(this->_threadGui, (void *)"test");
		}	
	}
}

bool	HandlePool::ping(Network *senderclt, int idSocketServer)
{
  senderclt->sendToSocket(idSocketServer, (void *)&"a", 1);
	senderclt->recvFromSocket();

	if ('b' == senderclt->get_buffer()[0])
		return true;
	else
		return false;
}
 
bool	HandlePool::receivePort(Network *senderclt, int idSocketServer)
{
	senderclt->sendToSocket(idSocketServer, (void *)_sconnect.roomname.c_str(), strlen(_sconnect.roomname.c_str()));
	senderclt->recvFromSocket();

	char	*buff = senderclt->get_buffer();

	unsigned long a = 0;
	a |= (buff[0] << 24);
	a |= (buff[1] << 16);
	a |= (buff[2] << 8);
	a |= buff[3];

	#ifdef _WIN32
	typedef unsigned __int32 uint32_t;
	uint32_t port = ntohl((uint32_t)a);
	#else
	int port = ntohl((int)a); //To test
	#endif

	if (port == 0)
	  return false;

	//envoie le port dans la class qui fait la reception
	
	this->_threadReception->setRoomPort(int(port));
	this->_threadGui->setRoomPort(int(port));

	if (senderclt->get_buffer() != NULL)
		return true;
	return false;
}

Window					*HandlePool::getWindow() const
{
	return this->_window;
}

Sound					*HandlePool::getSound() const
{
	return this->_sound;
}

ThreadPool				*HandlePool::getThreadPool() const
{
	return this->_threadPool;
}

CoreAction				*HandlePool::getThreadReception() const
{
	return this->_threadReception;
}
CoreGame				*HandlePool::getThreadGui() const
{
	return this->_threadGui;
}

Network					*HandlePool::getSocketPingServer() const
{
	return this->_socketPingServer;
}

Network					*HandlePool::getSocketInGame() const
{
	return this->_socketInGame;
}

Shared					*HandlePool::getClassShared() const
{
	return this->_classShared;
}

int						HandlePool::getIdSocketServer(void) const
{
	return this->_idSocketServer;
}

int						HandlePool::getIdSocketRoom(void) const
{
	return this->_idSocketRoom;
}
