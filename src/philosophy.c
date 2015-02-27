/*
** philosophy.c for philosophy in /home/tran_0/rendu/PSU_2014_philo
**
** Made by David Tran
** Login   <tran_0@epitech.net>
**
** Started on  Wed Feb 18 16:20:45 2015 David Tran
** Last update Fri Feb 27 22:55:21 2015 Johan Paasche
*/

#include "philosophers.h"

void		eat(t_philo *philo)
{
  philo->activity = EATING;
  sleep(1);
  philo->chopstick = 0;
  philo->rice -= 1;
  pthread_mutex_unlock(&g_chopstick[philo->nb]);
  pthread_mutex_unlock(&g_chopstick[(philo->nb + 1) % NB_PHILO]);
}

void		rest(t_philo *philo)
{
  philo->activity = SLEEPING;
  philo->chopstick = 0;
  sleep(1);
  if (philo->l->activity + philo->r->activity < 3 || philo->r->activity == SLEEPING)
    {
      if (pthread_mutex_trylock(&g_chopstick[philo->nb]) == 0)
	{
	  philo->chopstick += 1;
	  if (philo->l->activity <= THINKING && philo->r->activity < EATING)
	  if (pthread_mutex_trylock(&g_chopstick[(philo->nb + 1) % NB_PHILO]) == 0)
	    philo->chopstick += 1;
	}
    }
}

void		think(t_philo *philo)
{
  philo->activity = THINKING;
  sleep(1);
  /* pthread_mutex_unlock(&g_chopstick[(philo->nb + 1) % NB_PHILO]); */
  if ((philo->l->activity <= THINKING && philo->r->activity < THINKING) || philo->r->activity == SLEEPING)
    if (pthread_mutex_lock(&g_chopstick[(philo->nb + 1) % NB_PHILO]) == 0)
      {
	philo->chopstick += 1;
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
      if (philo->rice <= 0)
	return (NULL);
      fct[philo->chopstick](philo);
    }
  pthread_exit(0);
}
