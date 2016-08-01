#ifdef _WIN32
#else
#include	"UDLLoader.hh"

UDLLoader::UDLLoader()
{
}

UDLLoader::UDLLoader(UDLLoader const &other)
{
  this->_func = other._func;
  this->_handle = other._handle;
}

UDLLoader	&UDLLoader::operator=(UDLLoader const &other)
{
  if (this != &other)
    {
      this->_func = other._func;
      this->_handle = other._handle;
    }
  return (*this);
}

UDLLoader::~UDLLoader()
{
}

bool		UDLLoader::openLib(const char *libname, int flag)
{
  std::cout << "libname == " << libname << std::endl;
  this->_handle = dlopen(libname, flag);
  if (!this->_handle) {
	  std::cerr << "dlopen() failed." << std::endl;
	  return (false);
  }
  dlerror();
  return (true);
}

void *UDLLoader::getOpenLib() const
{
	return (this->_handle);
}

void		*UDLLoader::loadSym()
{
  // _func = NULL;
  // _func = dlsym(_handle, ENTRY_POINT);
  //std::cout << "coucou 1" << std::endl;
  _func = dlsym(_handle, "getPtr");
  ILevels *tmp = (reinterpret_cast<ILevels *(*)()>(_func)());
  //std::cout << "coucou 3" << std::endl;
  return ((void *)tmp);
}

int		UDLLoader::closeLib(IEntities *module)
{
  delete module;
  return (dlclose(this->_handle));
}

#endif
