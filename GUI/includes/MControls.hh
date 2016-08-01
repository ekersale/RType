#ifndef _M_CONTROLS_HH__
# define _M_CONTROLS_HH__

#include <map>
#include "IMenu.hh"

class MControl : public IMenu
{
public:
	MControl(Window *);
	~MControl();

	bool init();
	bool chooseImg();
	bool start();

private:
	std::map<int, sf::Sprite *> _img;
	Window *_wind;
	int _mx;
	bool _quitMenu;
};

#endif // !_M_CONTROLS_HH__
