#ifndef			SCOPEDLOCK_HH_
#define			SCOPEDLOCK_HH_

#include		<unistd.h>
#include		"Mutex.hh"

class			ScopedLock
{
 private:
  Mutex			*mutex;
 public:
  ScopedLock(Mutex * const &);
  ~ScopedLock();
};

#endif
