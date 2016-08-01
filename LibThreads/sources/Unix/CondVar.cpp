#include		"CondVar.hh"

CondVar::CondVar(Mutex * const &mutex_)
{
  mutex = mutex_;
  pthread_cond_init(&cond, NULL);
}

CondVar::~CondVar(void)
{
  pthread_cond_destroy(&cond);
}

void			CondVar::wait(void)
{
  pthread_cond_wait(&cond, mutex->getMutex());
}

void			CondVar::signal(void)
{
  pthread_cond_signal(&cond);
}