/*
** display.c for Philosophers in /home/paasch_j/work/PSU/PSU_2014_philo
**
** Made by Johan Paasche
** Login   <paasch_j@epitech.net>
**
** Started on  Sat Feb 21 14:35:47 2015 Johan Paasche
** Last update Wed Feb 25 21:14:37 2015 David Tran
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

void		display_bmp(t_state state, t_allin *allin, int pars)
{
  allin->positionFond.x = (pars % 6) * 160 + 50;
  allin->positionFond.y = (pars / 6) * 230 + 50;
  if (state == EATING)
    {
      allin->imageDeFond = SDL_LoadBMP("./mouth.BMP");
      SDL_BlitSurface(allin->imageDeFond, NULL, allin->ecran, &allin->positionFond);
      SDL_Flip(allin->ecran);
    }
  else if (state == SLEEPING)
    {
      allin->imageDeFond = SDL_LoadBMP("./eyes.BMP");
      SDL_BlitSurface(allin->imageDeFond, NULL, allin->ecran, &allin->positionFond);
      SDL_Flip(allin->ecran);
    }
  else
    {
      allin->imageDeFond = SDL_LoadBMP("./ears.BMP");
      SDL_BlitSurface(allin->imageDeFond, NULL, allin->ecran, &allin->positionFond);
      SDL_Flip(allin->ecran);
    }
}

void		*display_state(void *all_philos)
{
  int		pars;
  t_allin	*allin;
  t_philo	*aff_all;

  pars = 0;
  allin = (t_allin *)all_philos;
  aff_all = allin->philos;
  while (INFINITE_LOOP)
    {
      if (allin->go_out == TRUE)
	return (NULL);
      system("clear");
      SDL_FillRect(allin->ecran, NULL, 0x000000);
      pars = 0;
      while (pars < NB_PHILO)
	{
	  display_bmp(aff_all[pars].activity, allin, pars);
	  display_philosopher(&aff_all[pars]);
	  ++pars;
	}
      sleep(ACTION_TIME);
    }
  return (NULL);
}
