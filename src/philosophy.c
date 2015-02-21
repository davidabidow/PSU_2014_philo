/*
** philosophy.c for philosophy in /home/tran_0/rendu/PSU_2014_philo
**
** Made by David Tran
** Login   <tran_0@epitech.net>
**
** Started on  Wed Feb 18 16:20:45 2015 David Tran
** Last update Sat Feb 21 19:25:27 2015 Johan Paasche
*/

#include "philosophers.h"

void		eat(t_philo *philo)
{
  /* philo->activity = EATING; */
  philo->activity = THINKING;
  philo->rice = (philo->rice == 0 ? 0 : philo->rice - 1);
}

void		rest(t_philo *philo)
{
  /* philo->activity = SLEEPING; */
  philo->activity = EATING;
}

void		think(t_philo *philo)
{
  /* philo->activity = THINKING; */
  philo->activity = SLEEPING;
}

void		take_chopstick(UNUSED t_philo *philo)
{
  if (philo->activity == EATING)
    {
      pthread_mutex_unlock(&g_chopstick[philo->nb]);
      pthread_mutex_unlock(&g_chopstick[(philo->nb + 1) % NB_PHILO]);
      philo->chopstick = 0;
      philo->activity = SLEEPING;
      return;
    }
  if (pthread_mutex_trylock(&g_chopstick[philo->nb]) != 0)
    {
      pthread_mutex_unlock(&g_chopstick[philo->nb]);
      pthread_mutex_unlock(&g_chopstick[(philo->nb + 1) % NB_PHILO]);
      philo->chopstick = 0;
      philo->activity = SLEEPING;
      return;
    }
  else if (pthread_mutex_trylock(&g_chopstick[(philo->nb + 1) % NB_PHILO]) != 0)
    {
      philo->chopstick = 1;
      philo->activity = THINKING;
      return;
    }
  else
    {
      philo->chopstick = 2;
      philo->activity = EATING;
      return;
    }
}

void		*make_them_work(void *arg)
{
  t_philo	*philo;
  void		(*fct[3])(t_philo *);

  philo = (t_philo *)arg;
  fct[0] = &rest;
  fct[1] = &think;
  fct[2] = &eat;
  while (INFINITE_LOOP)
    {
      /* display_philosopher(philo); */
      take_chopstick(philo);
      fct[philo->activity](philo);
      sleep(ACTION_TIME);
    }
  pthread_exit(0);
}
