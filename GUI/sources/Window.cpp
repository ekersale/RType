#include "Windows.hh"

Window::Window()
{
	window = new sf::RenderWindow;
	event = new sf::Event;
	_icon = new sf::Image;
	window->setKeyRepeatEnabled(false);
}

Window::~Window()
{
	if (window != NULL)
		delete window;
}

void Window::createWindow()
{
	window->create(sf::VideoMode(1280, 720), "R-Type 0.6", sf::Style::Close | sf::Style::None);

	/*if (!_icon->loadFromFile("./Images/icones/logo.png"))
		EXIT_FAILURE;

	window->setIcon(480, 100, _icon->getPixelsPtr());*/

}

sf::Event *Window::getEvent() const
{
	window->pollEvent(*event);
	return (event);
}

sf::RenderWindow *Window::getWindow() const
{
	return (window);
}

void Window::destroyWindow()
{
	delete window;
	window = NULL;
}

