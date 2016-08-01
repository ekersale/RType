#include		"ScopedLock.hh"

ScopedLock::ScopedLock(Mutex * const &_mutex)
{
    mutex = _mutex;
    while (mutex->trylock() == false)
        usleep(WAIT_TIME);
}

ScopedLock::~ScopedLock()
{
    this->mutex->unlock();
}
