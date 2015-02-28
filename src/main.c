/*
** main.c for Philosophes in /home/paasch_j/rendu/PSU_2014_philo/src
**
** Made by Johan Paasche
** Login   <paasch_j@epitech.net>
**
** Started on  Tue Feb 17 01:09:27 2015 Johan Paasche
** Last update Sat Feb 28 23:51:30 2015 David Tran
*/

#include "philosophers.h"

int		init_philo_struct(t_allin *group)
{
  t_philo	*philos;
  int		pars;

  pars = 0;
  philos = group->philos;
  while (pars < group->nb_philo)
    {
      philos[pars].state = SLEEPING;
      philos[pars].chopstick = 0;
      philos[pars].rice = group->rice_qty;
      if (pthread_mutex_init(&philos[pars].m_chopstick, NULL) != 0)
	return (EXIT_FAILURE);
      philos[pars].nb = pars;
      philos[pars].name = "Platon";
      philos[pars].grp = group;
      if (pars > 0)
	{
	  philos[pars].l = &philos[pars - 1];
	  philos[pars - 1].r = &philos[pars];
	}
      pars++;
    }
  philos[pars - 1].r = &philos[0];
  philos[0].l = &philos[pars - 1];
  return (EXIT_SUCCESS);
}

void		launch_threads(t_allin	*care)
{
  pthread_t	display;
  int		pars;

  pars = 0;
  if (pthread_create(&display, NULL, display_state, care) != 0)
      return ;
  while (pars < care->nb_philo)
    {
      if (pthread_create(&(care->philos[pars].life),
			 NULL, make_them_work, &care->philos[pars]) != 0)
	return ;
      pars++;
    }
  pars = 0;
  while (pars < care->nb_philo)
    {
      if (pthread_join(care->philos[pars].life, NULL) != 0)
	return ;
      pars++;
    }
  if (pthread_join(display, NULL) != 0)
    return ;
}

void		init_care_struct(t_allin *care, int ac, char **av)
{
  int		nb;

  care->nb_philo = NB_PHILO;
  care->rice_qty = RICE;
  care->background_pos.x = 0;
  care->background_pos.y = 0;
  care->go_out = FALSE;
  if (ac >= 2)
    {
      if (((nb = atoi(av[1])) >= 5) && nb <= 1000)
	care->nb_philo = nb;
    }
  if (ac >= 3)
    if ((nb = atoi(av[2])) >= 1)
      care->rice_qty = nb;

}

int		main(int ac, char **av)
{
  t_allin	care;

  init_care_struct(&care, ac, av);
  if ((SDL_Init(SDL_INIT_VIDEO)) == -1 || init_sound(&care) == -1)
    return (EXIT_FAILURE);
  care.screen = SDL_SetVideoMode(1000, 1000, 32, SDL_HWSURFACE);
  SDL_WM_SetCaption("PSU_2014_philo !", NULL);
  if (!(care.philos = malloc(sizeof(t_philo) * care.nb_philo)))
    return (EXIT_FAILURE);
  if (init_philo_struct(&care) != EXIT_SUCCESS)
    return (0);
  init_font(&care);
  intro_screen(&care);
  launch_threads(&care);
  free(care.philos);
  FMOD_Sound_Release(care.musique);
  FMOD_System_Close(care.system);
  FMOD_System_Release(care.system);
  TTF_CloseFont(care.police);
  TTF_Quit();
  SDL_FreeSurface(care.texte);
  return (EXIT_SUCCESS);
}
