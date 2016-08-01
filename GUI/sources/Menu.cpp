#include "Menu.hh"

Menu::Menu(Window *wind, Sound *sound) : _wind(wind), _sound(sound)
{
	_launchGame = false;
	_mx = 1;
	_controls = new MControl(_wind);
	_options = new MOptions(_wind, _sound);
	_play = new MGame(_wind);
}

Menu::~Menu()
{
}

bool Menu::init()
{
	sf::Texture *tmp = new sf::Texture;
	sf::Sprite *sprite = new sf::Sprite;

	if (!tmp->loadFromFile("./assets/Images/menu-0.jpg"))
		return (false);
	sprite->setTexture(*tmp, true);
	sprite->setPosition(0, 0);
	_img[0] = sprite;
	tmp = new sf::Texture;
	sprite = new sf::Sprite;
	if (!tmp->loadFromFile("./assets/Images/menu-0-1.jpg"))
		return (false);
	sprite->setTexture(*tmp, true);
	sprite->setPosition(0, 0);
	_img[1] = sprite;
	tmp = new sf::Texture;
	sprite = new sf::Sprite;
	if (!tmp->loadFromFile("./assets/Images/menu-0-2.jpg"))
		return (false);
	sprite->setTexture(*tmp, true);
	sprite->setPosition(0, 0);
	_img[2] = sprite;
	tmp = new sf::Texture;
	sprite = new sf::Sprite;
	if (!tmp->loadFromFile("./assets/Images/menu-0-3.jpg"))
		return (false);
	sprite->setTexture(*tmp, true);
	sprite->setPosition(0, 0);
	_img[3] = sprite;
	tmp = new sf::Texture;
	sprite = new sf::Sprite;
	if (!tmp->loadFromFile("./assets/Images/menu-0-4.jpg"))
		return (false);
	sprite->setTexture(*tmp, true);
	sprite->setPosition(0, 0);
	_img[4] = sprite;
	if (_controls->init() == false || _options->init() == false || _play->init() == false)
	{
#ifdef _WIN32
		int msgboxID = MessageBox(NULL,
			(LPCSTR)"Check if Image folder is present in you computer",
			(LPCSTR)"Resource not available",
			MB_ICONERROR | MB_OK
			);
#else
		std::cerr << "Loading objects failed" << std::endl;
#endif
		return (true);
	}
	return (true);
}

IMenu *Menu::getOptions() const
{
	return (_options);
}

IMenu *Menu::getRoom() const
{
	return (_play);
}

bool Menu::launchSMenu()
{
	switch (_mx)
	{
	case 1 :
		if (_play->start() == false)
			return false;
		break;
	case 2:
		if (_options->start() == false)
			return (false);
		break;
	case 3:
		if (_controls->start() == false)
			return (false);
		break;
	case 4:
		return (false);
		break;
	}
	return (true);
}

bool Menu::chooseImg()
{
	sf::Event *tmp = _wind->getEvent();

	if (tmp->type == sf::Event::Closed)
	{
		_wind->getWindow()->close();
		return (false);
	}
	if (tmp->type == sf::Event::KeyPressed)
	{
		switch (tmp->key.code)
		{
		case sf::Keyboard::Left:
			if (_mx == 2 || _mx == 4)
				_mx -= 1;
			break;
		case sf::Keyboard::Right:
			if (_mx == 1 || _mx == 3)
				_mx += 1;
			break;
		case sf::Keyboard::Up:
			if (_mx == 3 || _mx == 4)
				_mx -= 2;
			break;
		case sf::Keyboard::Down:
			if (_mx == 1 || _mx == 2)
				_mx += 2;
			break;
		case sf::Keyboard::Return:
			if (launchSMenu() == false)
				return (false);
			break;
		default:
			break;
		}
	}
	return (true);
}

bool Menu::start()
{
	_sound->playMusic("menu", true);
	while (_launchGame != true)
	{
		if (chooseImg() == false)
			return (false);
		_wind->getWindow()->clear();
		_wind->getWindow()->draw(*(_img[_mx]));
		_wind->getWindow()->display();
		if (reinterpret_cast<MGame*>(_play)->getRoom() != "" && reinterpret_cast<MOptions*>(_options)->getIpAddr() != "" && reinterpret_cast<MOptions*>(_options)->getPort() != "")
	  _launchGame = true;
	}
	_sound->stopMusic("menu");
	return(true);
}
