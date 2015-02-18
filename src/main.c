/*
** main.c for Philosophes in /home/paasch_j/rendu/PSU_2014_philo/src
**
** Made by Johan Paasche
** Login   <paasch_j@epitech.net>
**
** Started on  Tue Feb 17 01:09:27 2015 Johan Paasche
** Last update Wed Feb 18 17:54:09 2015 Johan Paasche
*/

#include "philosophers.h"

int	init_mutex()
{
  int	pars;

  pars = 0;
  while (pars < NB_PHILO)
    {
      if (pthread_mutex_init(&g_chopstick[pars], NULL) != 0)
	return (EXIT_FAILURE);
      pars++;
    }
  return (EXIT_SUCCESS);
}

void	init_philo_struct(t_philo *philos)
{
  int	pars;

  pars = 0;
  while (pars < NB_PHILO)
    {
      philos[pars].activity = THINKING;
      philos[pars].chopstick = 0;
      philos[pars].restored = 0;
      philos[pars].rice = RICE;
      philos[pars].nb = pars;
      pars++;
    }
}

void	launch_threads(t_philo *philos)
{
  int	pars;

  pars = 0;
  while (pars < NB_PHILO)
    {
      if (pthread_create(&(philos[pars].life), NULL, make_them_work, &philos[pars]) != 0)
	return ;
      pars++;
    }
  pars = 0;
  while (pars < NB_PHILO)
    {
      if (pthread_join(philos[pars].life, NULL) != 0)
	return ;
      pars++;
    }
}

int		main(void)
{
  t_philo	*philos;

  if (!(philos = malloc(sizeof(t_philo) * 7)))
    return (EXIT_FAILURE);
  if (init_mutex() == EXIT_FAILURE)
    return (EXIT_FAILURE);
  init_philo_struct(philos);
  launch_threads(philos);
  return (printf("We are the philosophers.\n"));
}
