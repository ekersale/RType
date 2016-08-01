#ifndef _M_OPTIONS_HH__
# define _M_OPTIONS_HH__

#include <map>
#include "IMenu.hh"
#include "Sound.hh"

class MOptions : public IMenu
{
public:
	MOptions(Window *, Sound *);
	~MOptions();

	bool init();
	bool loadImg(const int &, const std::string &);
	bool chooseImg();
	bool start();
	std::string getIpAddr() const;
	std::string getPort() const;
	bool getVideoEnable() const;
	bool getConversationEnable() const;

private:
	Window *_wind;
	Sound *_sound;
	sf::Font *_font;
	std::map<int, sf::Sprite *> _img;
	std::string _ipaddr;
	std::string _port;
	int _mx;
	bool _audio;
	bool _video;
	bool _quitMenu;
};

#endif // !_M_OPTIONS_HH__
