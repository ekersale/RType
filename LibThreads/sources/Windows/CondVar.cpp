#include		"CondVar.hh"

CondVar::CondVar(Mutex * const &mutex_)
{
  mutex = mutex_;
  cond = CreateEvent(0, FALSE, FALSE, 0);
}

CondVar::~CondVar(void)
{
    CloseHandle(cond);
}

void			CondVar::wait(void)
{
    WaitForSingleObject(cond, INFINITE);    
}

void			CondVar::signal(void)
{
    SetEvent(cond);
}
