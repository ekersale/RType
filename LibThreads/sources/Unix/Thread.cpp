#include		"Thread.hh"

Thread::Thread(void)
{
    status = UNLAUNCHED;
    thread = -1;
}

Thread::~Thread(void)
{
    status = DEAD;
}

static void             *threadCLang(void * arguments)
{
    threadParameters    *arguments_c = reinterpret_cast<threadParameters *>(arguments);

    arguments_c->thread->runCode(arguments_c->parameters);
    delete arguments_c;
    return (NULL);
}

bool			Thread::waitThread(void)
{
    if (status == UNLAUNCHED)
        return (false);
    if (pthread_join(thread, NULL) == 0)
        return (true);
    return (false);
}

void			Thread::endThread(void)
{
    void                *ret = NULL;
    
    status = DEAD;
    pthread_cancel(thread);
}

bool			Thread::startThread(void * parameters)
{
    threadParameters    *tp;
    
    if (status != UNLAUNCHED)
        return (false);
    tp = new threadParameters;
    tp->parameters = parameters;
    tp->thread = this;
    if (pthread_create(&thread, NULL, threadCLang, tp) == 0) {
        status = PENDING;
        return (true);
    }
    return (false);
}
int                     Thread::get_status(void) const {
    return (status);
}
