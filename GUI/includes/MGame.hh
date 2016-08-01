#ifndef _M_GAME_H__
# define _M_GAME_H__

#include <map>
#include "IMenu.hh"

class MGame : public IMenu
{
public:
	MGame(Window *);
	~MGame();

	bool init();
	bool loadImg(const int &, const std::string &);
	bool chooseImg();
	bool start();
	std::string getRoom() const;

private:
	Window *_wind;
	sf::Font *_font;
	std::map<int, sf::Sprite *> _img;
	std::string _room;
	int _mx;
	bool _quitMenu;
	sf::Text _txt;
};

#endif // !_M_GAME_H__