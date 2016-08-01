#ifndef _ILEVEL_HH__
# define _ILEVEL_HH__

#include <vector>
#include "Elems.hh"

class ILevels
{
public:
	virtual std::vector<std::vector<std::vector<t_stage *>>> getStages() = 0;
};

#endif // !_ILEVEL_HH__
