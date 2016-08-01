#include		 "Mutex.hh"

Mutex::Mutex(void)
{
    locked = false;
    InitializeCriticalSection(&mutex);
}

Mutex::~Mutex(void)
{
    DeleteCriticalSection(&mutex);
}

void			Mutex::lock(void)
{
    EnterCriticalSection(&mutex);
    locked = true;
}

void			Mutex::unlock(void)
{
    LeaveCriticalSection(&mutex);
    locked = false;
}

bool			Mutex::trylock(void)
{
    if (TryEnterCriticalSection(&mutex) != 0) {
        if (locked == false) {
            locked = true;
            return (true);
        }
    }
    return (false);
}

void                    Mutex::trylockSleep(void)
{
    while (trylock() == false)
        Sleep(WAIT_TIME);
}

CRITICAL_SECTION*        Mutex::getsMutex(void)
{
    return (&mutex);
}
