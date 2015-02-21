/*
** philosophy.c for philosophy in /home/tran_0/rendu/PSU_2014_philo
**
** Made by David Tran
** Login   <tran_0@epitech.net>
**
** Started on  Wed Feb 18 16:20:45 2015 David Tran
** Last update Fri Feb 20 02:34:44 2015 David Tran
*/

#include "philosophers.h"

void	*make_them_work(void *philos)
{
  while (INFINITE_LOOP)
    {
      
    }
}

void		*display_state(void *all_philos)
{
  int		pars;
  t_philo	*aff_all;

  pars = 0;
  aff_all = (t_philo *)all_philos;
  while (pars < NB_PHILO)
    {
      printf("name : %s, state : %d, \n", aff_all->name, aff_all->activity);
      pars++;
    }
  return (NULL);
}
