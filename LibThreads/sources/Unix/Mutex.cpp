#include		 "Mutex.hh"

Mutex::Mutex(void)
{
    pthread_mutex_init(&mutex, NULL);
}

Mutex::~Mutex(void)
{
    pthread_mutex_destroy(&mutex);
}

void			Mutex::lock(void)
{
    pthread_mutex_lock(&mutex);
}

void			Mutex::unlock(void)
{
    pthread_mutex_unlock(&mutex);
}

bool			Mutex::trylock(void)
{
    if (pthread_mutex_trylock(&mutex) == 0)
        return (true);
    return (false);
}

void                    Mutex::trylockSleep(void)
{
    while (trylock() == false)
        usleep(WAIT_TIME);
}

pthread_mutex_t*        Mutex::getMutex(void)
{
    return (&mutex);
}
