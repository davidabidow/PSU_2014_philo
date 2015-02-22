/*
** main.c for Philosophes in /home/paasch_j/rendu/PSU_2014_philo/src
**
** Made by Johan Paasche
** Login   <paasch_j@epitech.net>
**
** Started on  Tue Feb 17 01:09:27 2015 Johan Paasche
** Last update Sun Feb 22 15:39:08 2015 Johan Paasche
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
      philos[pars].chopstick = 1;
      philos[pars].restored = 0;
      philos[pars].rice = RICE;
      philos[pars].nb = pars;
      philos[pars].name = "Platon";
      if (pars > 0)
	{
	  philos[pars].l = &philos[pars - 1];
	  philos[pars - 1].r = &philos[pars];
	}
      pars++;
    }
  philos[pars - 1].r = &philos[0];
}

void		launch_threads(t_philo *philos)
{
  pthread_t	display;
  int		pars;

  pars = 0;
  if (pthread_create(&display, NULL, display_state, philos) != 0)
      return ;
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
  if (pthread_join(display, NULL) != 0)
    return ;
}

int		main(void)
{
  t_philo	*philos;

  if (!(philos = malloc(sizeof(t_philo) * NB_PHILO)))
    return (EXIT_FAILURE);
  if (init_mutex() == EXIT_FAILURE)
    return (EXIT_FAILURE);
  init_philo_struct(philos);
  launch_threads(philos);
  free(philos);
  return (0);
}
