#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "MGame.hh"

MGame::MGame(Window *wind) : _wind(wind)
{
	_quitMenu = false;
	_mx = 0;
	_room = "";
}

MGame::~MGame() {
}

bool MGame::init()
{
	_font = new sf::Font;
	_txt.setFont(*_font);
	_txt.setCharacterSize(40);
	_txt.setColor(sf::Color::Yellow);
	_txt.setPosition(215, 300);
	if (!_font->loadFromFile("./assets/Fonts/TAHOMA.TTF"))
		return (false);

	sf::Texture *tmp = new sf::Texture;
	sf::Sprite *sprite = new sf::Sprite;
	
	if (!tmp->loadFromFile("./assets/Images/menu-3.png"))
		return (false);
	
	sprite->setTexture(*tmp, true);
	sprite->setPosition(0, 0);
	_img[0] = sprite;
	(void)tmp;
	return (true);
}

bool MGame::chooseImg()
{
	sf::Event *tmp = _wind->getEvent();

	switch (tmp->type)
	{
	case sf::Event::Closed:
		_wind->getWindow()->close();
		return (false);
		break;
	case sf::Event::TextEntered:
		if (_room.length() <= 32 && tmp->text.unicode >= 'a' && tmp->text.unicode <= 'z' ||
			_room.length() <= 32 && tmp->text.unicode >= 'A' && tmp->text.unicode <= 'Z') {
			_room += static_cast<char>(tmp->text.unicode);
		}
		break;
	case sf::Event::KeyPressed:
		switch (tmp->key.code)
		{
		case sf::Keyboard::BackSpace:
			if (!_room.empty()) {
				_room.pop_back();
			}
			break;
		case sf::Keyboard::Escape:
			_quitMenu = true;
			break;
		case sf::Keyboard::Return:
			if (_room.length() <= 0) {
				_txt.setColor(sf::Color::Red);
				_txt.setString("Veuillez indiquer un nom de room.");
				_wind->getWindow()->draw(_txt);
				_wind->getWindow()->display();
				_txt.setColor(sf::Color::Yellow);
#ifdef _WIN32
				Sleep(3000);
#else
				usleep(3000000); // TODO elliot
#endif
			}
			else {
				_quitMenu = true;
				return (true);
			}
			break;
		default:
			break;
		}
	}
#ifdef _WIN32
	Sleep(50);
#else
	usleep(50000);
#endif
	return (true);
}

std::string MGame::getRoom() const
{
	return (_room);
}

bool MGame::start()
{
	while (_quitMenu != true)
	{
		if (chooseImg() == false)
			return (false);
		_txt.setString(_room);
		_wind->getWindow()->clear();
		_wind->getWindow()->draw(*(_img[0]));
		
		_wind->getWindow()->draw(_txt);
		_wind->getWindow()->display();
	}
	_quitMenu = false;
	return (true);
}