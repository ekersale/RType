/*
 ** test.h for test in /home/urvoy_p/Desktop/lib_threads
 ** 
 ** Made by Pierre-Antoine Urvoy
 ** Login   <urvoy_p@epitech.net>
 ** 
 ** Started on  Tue Nov 25 13:43:01 2014 Pierre-Antoine Urvoy
 // Last update Sun Dec 21 18:00:34 2014 Pierre-Antoine Urvoy
 */

#ifndef THREADS_TEST_HH_
#define THREADS_TEST_HH_

#include "Thread.hh"
#include "ThreadPool.hh"
#include <stdio.h>

Mutex           *mutex =  new Mutex();

class Buff : public Thread //on invente ensuite ici un Objet Threadé bidon
{
public:
    std::string *str;
    Buff(void) : Thread() {str = new std::string("toto");};
    ~Buff(void) {};
    std::string *getStr() {
        return (str);
        
    };
    void runCode(void * argument) {
        while (1) {
            const char *p = (*getStr()).data();
            while (*p)
                p++;
        }
    }
};

class Room : public Thread //on invente ensuite ici un Objet Threadé bidon
{
public:
    Buff *buff;
    Room(void) : Thread() {buff = new Buff();};
    ~Room(void) {};
    void runCode(void * argument) {
        ThreadPool * pool = reinterpret_cast<ThreadPool *>(argument);
        
        pool->scheduleThread(buff, (void *)"jj");
        while (1) {
            const char *p = (*buff->getStr()).data();
            while (*p)
                std::cout << p++ << std::endl;
        }
    }
};

class handlePool : public Thread //ceci est lobjet qui va threader le fonctionnement de la threadpool (agir sur elle sans passer par le main())
{
public: //le handlePool est le thread principal: il peut gèrer tous les autres
    handlePool(void) : Thread() {};
    ~handlePool(void) {};
    void runCode(void * handlePool) {
        ThreadPool * pool = reinterpret_cast<ThreadPool *>(handlePool); //la ThreadPool est recue en paramètre dans cette fonction
        Room *rm = new Room();
        
        pool->scheduleThread(rm, (void *)pool);
    };
};

#endif
