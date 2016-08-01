#ifndef _MENU_HH__
# define _MENU_HH__

#include <map>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "IMenu.hh"
#include "Sound.hh"
#include "MControls.hh"
#include "MOptions.hh"
#include "MGame.hh"

class Menu : public IMenu
{
public:
	Menu(Window *, Sound *);
	~Menu();

	bool init();
	bool start();
	bool chooseImg();
	bool launchSMenu();
	IMenu *getOptions() const;
	IMenu *getRoom() const;

private:
	Window *_wind;
	Sound *_sound;
	IMenu *_controls;
	IMenu *_options;
	IMenu *_play;
	std::map<int, sf::Sprite *> _img;
	bool _launchGame;
	int _mx;
};


#endif // !_MENU_HH__
