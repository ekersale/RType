#ifdef _WIN32

#include "WDLLoader.hh"

WDLLoader::WDLLoader()
{
}

WDLLoader::WDLLoader(WDLLoader const &other)
{
	this->_hinstLib = other._hinstLib;
	this->_ProcAdd = other._ProcAdd;
}

WDLLoader	&WDLLoader::operator=(WDLLoader const &other)
{
	if (this != &other)
	{
		this->_hinstLib = other._hinstLib;
		this->_ProcAdd = other._ProcAdd;
	}
	return (*this);
}

WDLLoader::~WDLLoader()
{
}

bool		WDLLoader::openLib(const char *libname, int flag)
{
	(void)flag;
	_hinstLib = LoadLibrary(TEXT(libname)); //TEXT
	if (_hinstLib == NULL)
		return (false);
	return (true);
}

void		*WDLLoader::getOpenLib() const
{
	return (_hinstLib);
}

void		*WDLLoader::loadSym()
{
	_ProcAdd = (MYPROC)GetProcAddress(_hinstLib, "getPtr");
	return ((void *)(_ProcAdd)());
}

int			WDLLoader::closeLib(IEntities *module)
{
	delete module;
	return (FreeLibrary(_hinstLib));
}

#endif