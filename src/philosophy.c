/*
** philosophy.c for philosophy in /home/tran_0/rendu/PSU_2014_philo
**
** Made by David Tran
** Login   <tran_0@epitech.net>
**
** Started on  Wed Feb 18 16:20:45 2015 David Tran
** Last update Sat Feb 28 20:33:14 2015 Johan Paasche
*/

#include "philosophers.h"

void		eat(t_philo *philo)
{
  philo->state = EATING;
  philo->rice -= 1;
  sleep(ACTION_TIME);
  philo->chopstick = 0;
  if (philo->rice <= 0)
    philo->state = SLEEPING;
  pthread_mutex_unlock(&philo->m_chopstick);
  pthread_mutex_unlock(&philo->r->m_chopstick);
}

void		rest(t_philo *philo)
{
  philo->state = SLEEPING;
  philo->chopstick = 0;
  sleep(ACTION_TIME);
  if (philo->rice > 0)
    {
      if ((philo->l->state + philo->r->state < 3)
	  || philo->r->state == SLEEPING)
	{
	  if (pthread_mutex_trylock(&philo->m_chopstick) == 0)
	    {
	      philo->chopstick += 1;
	      if (philo->l->state <= THINKING && philo->r->state < EATING)
		if (pthread_mutex_trylock(&philo->r->m_chopstick) == 0)
		  philo->chopstick += 1;
	    }
	}
    }
}

void		think(t_philo *philo)
{
  philo->state = THINKING;
  sleep(ACTION_TIME);
  if ((philo->l->state <= THINKING && philo->r->state < THINKING)
      || philo->r->state == SLEEPING)
    if (pthread_mutex_lock(&philo->r->m_chopstick) == 0)
	philo->chopstick += 1;
}

void		*make_them_work(void *arg)
{
  t_philo	*philo;
  void		(*fct[3])(t_philo *);

  philo = (t_philo *)arg;
  fct[0] = &rest;
  fct[1] = &think;
  fct[2] = &eat;
  while (philo->rice > 0)
    {
      if (philo->rice <= 0)
	return (NULL);
      fct[philo->chopstick](philo);
    }
  pthread_exit(0);
}
