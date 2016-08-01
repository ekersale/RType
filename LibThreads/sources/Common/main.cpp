/*
** main.c for tp in /home/urvoy_p/TPTHREADS
** 
** Made by Pierre-Antoine Urvoy
** Login   <urvoy_p@epitech.net>
** 
** Started on  Wed Apr 16 14:20:08 2014 Pierre-Antoine Urvoy
// Last update Tue Nov 25 14:00:10 2014 Pierre-Antoine Urvoy
*/

#include                <stdlib.h>
#include                <iostream>
#include		"ThreadPool.hh"
#include		"Test.hh"


/* main */
int		main(void)
{
  ThreadPool		pool;
  handlePool            hPool;
  
  pool.scheduleThread(&hPool, (void *)&pool); //on crée une classe handlePool qui va thredder le fonctionnement de la threadPool #MAIN puis voir Test.h
  pool.waitThreads(); //ici ca devient bloquant
  return (0);
}
