#include "Windows.hh"
#include "Sound.hh"
#include "Menu.hh"
#include "CoreGame.hh"
#include "CoreAction.hh" //Réception des commandes
#include "Network.hh"
#include "ThreadPool.hh"
#include "HandlePool.hh"
#include "ThreadAudio.hh"

int	initialiazation()
{
	Menu			*menu;
	Window			*wind = new Window;
	Sound			*sound = new Sound;
	ThreadPool		pool;
	HandlePool		hPool;

	wind->createWindow();
	sound->init();
	menu = new Menu(wind, sound);
	if (menu->init() == false)
		return (-1);
	if (menu->start() == false)
		return (-1);
	_sconnect.roomname = reinterpret_cast<MGame*>(menu->getRoom())->getRoom();
	_sconnect.ip = reinterpret_cast<MOptions*>(menu->getOptions())->getIpAddr();
	_sconnect.port = reinterpret_cast<MOptions*>(menu->getOptions())->getPort();
	wind->destroyWindow();
	pool.scheduleThread(&hPool, (void *)&pool); //on crée une classe handlePool qui va thredder le fonctionnement de la threadPool #MAIN puis voir Test.h
	pool.waitThreads(); //ici ca devient bloquant
	return 0;
}

int main()
{
	initialiazation();
	return (1);
}
