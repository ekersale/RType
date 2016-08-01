#include "MControls.hh"

MControl::MControl(Window *wind) : _wind(wind)
{
	_quitMenu = false;
	_mx = 0;
}

MControl::~MControl() {
}

bool MControl::init()
{
	sf::Texture *tmp = new sf::Texture;
	sf::Sprite *sprite = new sf::Sprite;
	if (!tmp->loadFromFile("./assets/Images/menu-1-1.jpg"))
		return (false);
	sprite->setTexture(*tmp, true);
	sprite->setPosition(0, 0);
	_img[0] = sprite;
	tmp = new sf::Texture;
	sprite = new sf::Sprite;
	if (!tmp->loadFromFile("./assets/Images/menu-1-2.jpg"))
		return (false);
	sprite->setTexture(*tmp, true);
	sprite->setPosition(0, 0);
	_img[1] = sprite;
	(void)tmp;
	return (true);
}

bool MControl::chooseImg()
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
			if (_mx == 1)
				_mx -= 1;
			break;
		case sf::Keyboard::Right:
			if (_mx == 0)
				_mx += 1;
			break;
		case sf::Keyboard::Return:
			if (_mx == 0) {
				_quitMenu = true;
				return (true);
			}
			if (_mx == 1)
				return (false);
			break;
		default:
			break;
		}
	}
	return (true);
}

bool MControl::start()
{
	while (_quitMenu != true)
	{
		if (chooseImg() == false)
			return (false);
		_wind->getWindow()->clear();
		_wind->getWindow()->draw(*(_img[_mx]));
		_wind->getWindow()->display();
	}
	_quitMenu = false;
	return (true);
}