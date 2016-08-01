#ifdef _WIN32

#ifndef _WDLLOADER_HH__
# define _WDLLOADER_HH__

#include	<iostream>
#include	<windows.h>
#include	"IDLLoader.hh"

typedef int(__cdecl *MYPROC)();

class		WDLLoader : public IDLLoader
{

private:
	HINSTANCE	_hinstLib;
	MYPROC		_ProcAdd;

public:

	WDLLoader();
	WDLLoader(WDLLoader const &);
	~WDLLoader();

	WDLLoader &operator=(WDLLoader const &);

	bool		openLib(const char *, int);
	void		*getOpenLib() const;
	void		*loadSym();
	int			closeLib(IEntities *);
};

#endif // !_WDLLOADER_HH__

#endif