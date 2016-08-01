#include		"ThreadPool.hh"

ThreadPool::ThreadPool(void)
{
}

ThreadPool::~ThreadPool(void)
{
}

int                     ThreadPool::scheduleThread(Thread * threadedObject, void * arguments)
{
    if (threadedObject->startThread(arguments) == false)
        return (-1);
    threads.push(threadedObject);
   return (threads.size() - 1);
}

void                    ThreadPool::waitThreads(void)
{
    int                 i = -1;
    
    while (++i < (int)threads.size()) {
        threads.at(i)->waitThread();
    }
}

void                    ThreadPool::endThreads(void)
{
    int                 i = -1;
    
    while (++i < (int)threads.size())
        threads.at(i)->endThread();
        
}

void                    ThreadPool::endThread(int id)
{
    threads.at(id)->endThread();
}

int                    ThreadPool::size(void) 
{
    return ((int)threads.size());
}
