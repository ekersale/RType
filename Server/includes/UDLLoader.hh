#ifdef _WIN32
#else

#ifndef		_DLLOADER_HH_
#define		_DLLOADER_HH_

#include	<iostream>
#include	<dlfcn.h>
#include	"IDLLoader.hh"
#include	"ILevels.hh"

#define		ENTRY_POINT	"getPtr"

class		UDLLoader : public IDLLoader
{

private :
  void		*_handle;
  void		*_func;
public :

  UDLLoader();
  UDLLoader(UDLLoader const &);
  UDLLoader	&operator=(UDLLoader const &);
  ~UDLLoader();

  bool		openLib(const char *, int);
  void		*getOpenLib() const;
  void		*loadSym();
  int		closeLib(IEntities *);
};

#endif
#endif
