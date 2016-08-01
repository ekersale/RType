#ifndef _IDLLOADER_HH__
# define _IDLLOADER_HH__

#include "IEntities.hh"

class IDLLoader
{
public:
	virtual bool		openLib(const char *, int) = 0;
	virtual void		*getOpenLib() const = 0;
	virtual void		*loadSym() = 0;
	virtual int			closeLib(IEntities *) = 0;
};

#endif // !_IDLLOADER_HH__
