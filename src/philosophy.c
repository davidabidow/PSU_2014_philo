/*
** philosophy.c for philosophy in /home/tran_0/rendu/PSU_2014_philo
**
** Made by David Tran
** Login   <tran_0@epitech.net>
**
** Started on  Wed Feb 18 16:20:45 2015 David Tran
** Last update Sat Feb 21 16:10:58 2015 David Tran
*/

#include "philosophers.h"

void		eat(t_philo *philo)
{
  if (pthread_mutex_trylock(&g_chopstick[philo->nb]) == 0)
    {
      printf("philo [%d] has locked chopstick [%d]\n", philo->nb, philo->nb);
      philo->chopstick += 1;
    }
  if (pthread_mutex_trylock(&g_chopstick[philo->nb + 1 % NB_PHILO]) == 0)
    {
      printf("philo [%d] has locked chopstick [%d]\n", philo->nb, philo->nb + 1 % NB_PHILO);
      philo->chopstick += 1;
    }
  if (philo->chopstick == 2)
    {
      philo->rice -= 1;
      philo->activity = EATING;
      pthread_mutex_unlock(&g_chopstick[philo->nb]);
      pthread_mutex_unlock(&g_chopstick[philo->nb + 1 % NB_PHILO]);
      philo->restored  = TRUE;
      philo->chopstick = 0;
    }
  else
    {
      pthread_mutex_unlock(&g_chopstick[philo->nb]);
      pthread_mutex_unlock(&g_chopstick[philo->nb + 1 % NB_PHILO]);
      philo->restored  = FALSE;
      philo->chopstick = 0;
    }
}

void		rest(t_philo *philo)
{
  philo->activity = SLEEPING;
}

void		think(t_philo *philo)
{
  philo->activity = THINKING;
}

void		take_chopstick(UNUSED t_philo *philo)
{

}

void		*make_them_work(void *arg)
{
  t_philo	*philo;
  void		(*activity_fct[3])(t_philo *);

  philo = (t_philo *)arg;
  activity_fct[0] = &rest;
  activity_fct[1] = &think;
  activity_fct[2] = &eat;
  while (INFINITE_LOOP)
    {
      display_philosopher(philo);
      take_chopstick(philo);
      activity_fct[philo->chopstick](philo);
      sleep(1);
    }
  pthread_exit(0);
}
