/*
** display.c for Philosophers in /home/paasch_j/work/PSU/PSU_2014_philo
**
** Made by Johan Paasche
** Login   <paasch_j@epitech.net>
**
** Started on  Sat Feb 21 14:35:47 2015 Johan Paasche
** Last update Sat Feb 21 19:02:31 2015 Johan Paasche
*/

#include "philosophers.h"

void		display_activity(t_state state)
{
  if (state == EATING)
    printf("EATING...   ");
  else if (state == SLEEPING)
    printf("SLEEPING... ");
  else
    printf("THINKING... ");
}

void		display_philosopher(t_philo *philo)
{
  printf("[%s]  (Philosopher N° %d) is ", philo->name, philo->nb);
  display_activity(philo->activity);
  printf("He has got [%d] chopstick(s) and [%d] mouthful of rice left.\n", philo->chopstick, philo->rice);
}



void		*display_state(UNUSED void *all_philos)
{
  int		pars;
  t_philo	*aff_all;

  pars = 0;
  aff_all = (t_philo *)all_philos;
  while (INFINITE_LOOP)
    {
      system("clear");
      pars = 0;
      while (pars < NB_PHILO)
	{
	  display_philosopher(&aff_all[pars]);
	  ++pars;
	}
      sleep(ACTION_TIME);
    }
  return (NULL);
}
