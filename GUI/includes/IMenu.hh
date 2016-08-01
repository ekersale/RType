#ifndef _IMENU_HH__
# define _IMENU_HH__

#include "Windows.hh"

class IMenu
{
public :
	virtual bool init() = 0;
	virtual bool chooseImg() = 0;
	virtual bool start() = 0;
};

#endif // !_IMENU_HH__
