/*
** display.c for Philosophers in /home/paasch_j/work/PSU/PSU_2014_philo
**
** Made by Johan Paasche
** Login   <paasch_j@epitech.net>
**
** Started on  Sat Feb 21 14:35:47 2015 Johan Paasche
** Last update Wed Feb 25 01:38:14 2015 David Tran
*/

#include "philosophers.h"

void		display_activity(t_state state)
{
  if (state == EATING)
    printf(EATING_DISPLAY);
    /* printf("EATING...   "); */
  else if (state == SLEEPING)
    printf(SLEEPING_DISPLAY);
    /* printf("SLEEPING... "); */
  else
    printf(THINKING_DISPLAY);
    /* printf("THINKING... "); */
}

void		display_philosopher(t_philo *philo)
{
  printf("[%s]  (Philosopher N° %d) is ", philo->name, philo->nb + 1);
  display_activity(philo->activity);
  printf("He has got [%d] chopstick(s) and [%d] mouthful of rice left.\n", philo->chopstick, philo->rice);
}

void		display_bmp(t_state state)
{
  if (state == EATING)
    {
      imageDeFond = SDL_LoadBMP("./mouth.BMP");
      SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
      SDL_Flip(ecran);
    }
  else if (state == SLEEPING)
    {
      imageDeFond = SDL_LoadBMP("./eyes.BMP");
      SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
      SDL_Flip(ecran);
    }
  else
    {
      imageDeFond = SDL_LoadBMP("./ears.BMP");
      SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
      SDL_Flip(ecran);
    }
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
      SDL_FillRect(ecran, NULL, 0x000000);
      pars = 0;
      while (pars < NB_PHILO)
	{
	  positionFond.x = (pars % 5) * 200;
	  positionFond.y = (pars % 4) * 250;
	  display_bmp(aff_all[pars].activity);
	  display_philosopher(&aff_all[pars]);
	  ++pars;
	}
      sleep(ACTION_TIME);
    }
  return (NULL);
}
