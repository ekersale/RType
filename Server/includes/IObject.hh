#ifndef _IOBJECT_HH__
# define _IOBJECT_HH__

#include "Elems.hh"

class IObject
{
public:
	virtual void *update() = 0;
	virtual Rect getPos() = 0;
	virtual e_type getType() const = 0;
	virtual int getLevel() const = 0;
	virtual int getPower() const = 0;
	virtual void setPower(const int &) = 0;
	virtual int getLifePoint() const = 0;
	virtual bool setLifePoint(int) = 0;
	virtual Rect getSizeObj() const = 0;
	virtual int getId() const = 0;
	virtual void setId(const int &) = 0;
	virtual void setDRect(const DRect &) = 0;
	virtual void setBelongsTo(const int &) = 0;
	virtual bool getBelongsTo() const = 0;
	virtual int getReward() const = 0;
};

#endif // !_IOBJECT_HH__

