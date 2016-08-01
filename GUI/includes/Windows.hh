#ifndef _WINDOW_HH__
# define _WINDOW_HH__

#include <SFML/Graphics.hpp>
#include <iostream>

class Window
{
public:
	Window();
	~Window();

	void createWindow();
	void setFrameRate(int);
	sf::RenderWindow *getWindow() const;
	sf::Event *getEvent() const;
	void destroyWindow();

private:
	sf::RenderWindow *window;
	sf::Event *event;
	sf::Image	*_icon;
};


#endif //!_WINDOW_H__