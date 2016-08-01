#ifndef _OBJECT_PULL_HH__
# define _OBJECT_PULL_HH__

#include <vector>
#include <iostream>
#include <string>
#include "WDLLoader.hh"
#include "Stage.hh"
#include "Object.hh"

class ObjectPull
{
public:
	ObjectPull(std::vector<t_stage *> *);
	~ObjectPull();

	void createObj();
	std::vector<IObject *> *getObjs() const;

private:
	std::vector<IObject *> *_obj;
	std::vector<t_stage *> *_stage;
	int _id;
};

#endif // !_OBJECT_PULL_HH__
