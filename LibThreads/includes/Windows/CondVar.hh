#ifndef			CONDVAR_HH_
#define			CONDVAR_HH_

#include		"ICondVar.hh"
#include		"ScopedLock.hh"
#include		"Mutex.hh"
#include                <errno.h>
#include                <time.h>

class			CondVar : public ICondVar
{
 private:
  Mutex			*mutex;
  HANDLE                 cond;
 public:
  void			wait(void);
  void			signal(void);

  CondVar(Mutex * const &);
  ~CondVar();
};

#endif
