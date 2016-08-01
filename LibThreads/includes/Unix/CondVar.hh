#ifndef			CONDVAR_HH_
#define			CONDVAR_HH_

#include		"ICondVar.hh"
#include		"ScopedLock.hh"
#include		"Mutex.hh"
#include                <sys/time.h>
#include                <errno.h>
#include                <time.h>

class			CondVar : public ICondVar
{
 private:
  Mutex			*mutex;
  pthread_cond_t	cond;
 public:
  void			wait(void);
  void			signal(void);

  CondVar(Mutex * const &);
  ~CondVar();
};

#endif
