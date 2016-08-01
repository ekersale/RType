#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "MOptions.hh"

MOptions::MOptions(Window *wind, Sound *sound) : _wind(wind), _sound(sound)
{
	_quitMenu = false;
	_ipaddr = "127.0.0.1";
	_port = "2000";
}

MOptions::~MOptions()
{
}

bool MOptions::loadImg(const int &id, const std::string &path)
{
	sf::Texture *tmp;
	sf::Sprite *sprite;

	tmp = new sf::Texture;
	sprite = new sf::Sprite;
	if (!tmp->loadFromFile(path))
		return (false);
	sprite->setTexture(*tmp, true);
	sprite->setPosition(0, 0);
	_img[id] = sprite;
	return (true);
}

bool MOptions::init()
{
	_font = new sf::Font;
	if (!_font->loadFromFile("./assets/Fonts/MORPHEUS.TTF"))
		return (false);

	int id = 0;
	for (int i = 1; i <= 8; i++) {
		if (i == 4){
			if (!loadImg(id, "./assets/Images/menu-2-3-1.jpg"))
				return (false);
			id++;
		}
		if (i == 5) {
			if (!loadImg(id, "./assets/Images/menu-2-4-1.jpg"))
				return (false);
			id++;
		}
		if (i == 8) {
			if (!loadImg(id, "./assets/Images/menu-2-7-1.jpg"))
				return (false);
			id++;
			if (!loadImg(id, "./assets/Images/menu-2-7-2.jpg"))
				return (false);
			id++;
		}
		std::string path = "./assets/Images/menu-2-" + std::to_string(i);
		path += ".jpg";
		if (!loadImg(id, path))
			return (false);
		id++;
		if (i == 8) {
			if (!loadImg(id, "./assets/Images/menu-2-8-1.jpg"))
				return (false);
			id++;
			if (!loadImg(id, "./assets/Images/menu-2-8-2.jpg"))
				return (false);
		}
	}
	return (true);
}

bool MOptions::chooseImg()
{
	sf::Event *tmp = _wind->getEvent();
	switch (tmp->type)
	{
	case sf::Event::Closed:
		_wind->getWindow()->close();
		return (false);
		break;
	case sf::Event::TextEntered:
		if (tmp->text.unicode >= '0' && tmp->text.unicode <= '9' || tmp->text.unicode == '.') {
			if (_mx == 3)
				_ipaddr += static_cast<char>(tmp->text.unicode);
			if (_mx == 5 && tmp->text.unicode != '.')
				_port += static_cast<char>(tmp->text.unicode);
		}
		break;
	case sf::Event::KeyPressed:
		switch (tmp->key.code)
		{
		case sf::Keyboard::BackSpace:
		    if (_mx == 3 && !_ipaddr.empty())
		      _ipaddr.pop_back();
		    if (_mx == 5 && !_port.empty())
		      _port.pop_back();
		  break;
		case sf::Keyboard::Return:
			switch (_mx)
			{
			case 0:
				_quitMenu = true;
				return (true);
				break;
			case 1:
				return (false);
				break;
			case 2:
				_mx = 3;
				break;
			case 4:
				_mx = 5;
				break;
			case 6:
				_sound->soundUp(20);
				break;
			case 7:
				_sound->soundDown(20);
				break;
			case 8:
				_mx = 9;
				if (_audio == true)
					_audio = false;
				else 
					_audio = true;
				break;
			case 11:
				_mx = 12;
				if (_video == true)
					_video = false;
				else
					_video = true;
				break;

			}
			break;
		case sf::Keyboard::Right:
			if (_mx == 0 || _mx == 6 || _mx == 3 || _mx == 10)
				_mx += 1;
			if (_mx == 2 || _mx == 9)
				_mx += 2;
			if (_mx == 8)
				_mx += 3;
			break;
		case sf::Keyboard::Left:
			if (_mx == 1 || _mx == 5 || _mx == 7 || _mx == 11)
				_mx -= 1;
			if (_mx == 4 || _mx == 10)
				_mx -= 2;
			if (_mx == 12)
				_mx -= 4;
			break;
		case sf::Keyboard::Up:
			if (_mx == 3 || _mx == 4 || _mx == 9 || _mx == 7)
				_mx -= 3;
			else if (_mx == 6 || _mx == 10 || _mx == 11 || _mx == 5)
				_mx -= 4;
			else {
				if (_mx == 12)
					_mx -= 5;
				if (_mx == 13)
					_mx -= 6;
				if (_mx > 1)
					_mx -= 2;
			}
			break;
		case sf::Keyboard::Down:
			if (_mx == 0 || _mx == 6)
				_mx += 2;
			else if (_mx == 1 || _mx == 3 || _mx == 4)
				_mx += 3;
			else {
				if (_mx == 2 || _mx == 7)
					_mx += 4;
			}
			break;
		}
		break;
	default:
		break;
	}
	#ifdef _WIN32
	Sleep(75);
	#else
	usleep(75000); //TODO confirme Elliot
	#endif
	return (true);
}

std::string MOptions::getIpAddr() const
{
	return (_ipaddr);
}

std::string MOptions::getPort() const
{
	return (_port);
}

bool MOptions::getVideoEnable() const
{
	return (_video);
}

bool MOptions::getConversationEnable() const
{
	return (_audio);
}

bool MOptions::start()
{
	sf::Text txt;

	txt.setFont(*_font);
	txt.setCharacterSize(40);
	txt.setColor(sf::Color::Red);
	txt.setPosition(375, 510);
	while (_quitMenu != true)
	{
		if (chooseImg() == false)
			return (false);
		if (_mx == 2 || _mx == 3)
			txt.setString(_ipaddr);
		else if (_mx == 4 || _mx == 5)
			txt.setString(_port);
		else
			txt.setString("");
		_wind->getWindow()->clear();
		_wind->getWindow()->draw(*(_img[_mx]));
		_wind->getWindow()->draw(txt);
		_wind->getWindow()->display();
	}
	_quitMenu = false;
	return (true);
}
