/*
** philosophers.h for Philosophes in /home/paasch_j/rendu/PSU_2014_philo/include
**
** Made by Johan Paasche
** Login   <paasch_j@epitech.net>
**
** Started on  Tue Feb 17 01:13:05 2015 Johan Paasche
** Last update Fri Apr  3 16:50:58 2015 David Tran
*/

#ifndef		PHILOSOPHERS_H_
# define	PHILOSOPHERS_H_

# include	<unistd.h>
# include	<stdio.h>
# include	<pthread.h>
# include	<stdlib.h>
# include	<SDL/SDL.h>
# include	<SDL/SDL_image.h>
# include	<SDL/SDL_ttf.h>
# include	<SDL/SDL_mixer.h>

/*
** Number of philosophers, influencing the number of mutexs we gonna have
*/

# define	NB_PHILO	(7)

/*
** Let's introduce a quik funy rule while
** stopping the game if RICE (X) falls to 0.
*/

# define	RICE		(30)

/*
**	Just for paasch_j
*/

# define	INFINITE_LOOP	(42)


# define	ACTION_TIME	(1)

typedef	char t_bool;

# define	TRUE		(1)
# define	FALSE		(0)

# define	EATING_DISPLAY		"\033[34;01mEATING\033[00m ...   "
# define	SLEEPING_DISPLAY	"\033[35;01mSLEEPING\033[00m ... "
# define	THINKING_DISPLAY	"\033[36;01mTHINKING\033[00m ... "

# define	SLEEPING_MONKEY		"./imgBank/eyes.BMP"
# define	THINKING_MONKEY		"./imgBank/ears.BMP"
# define	EATING_MONKEY		"./imgBank/mouth.BMP"
# define	MUSIC_MONKEY		"./imgBank/Gorillaz.wav"
# define	SMOKE_MONKEY		"./imgBank/smoke.BMP"
# define	WRITE_MONKEY		"./imgBank/AlphaWood.ttf"

/*
** enum of state, we may introduce some other states ...
*/

typedef enum	e_state
{
  EATING = 0,
  SLEEPING,
  THINKING
}		t_state;

/*
** This represents a philosopher
*/

typedef	struct		s_philo
{
  pthread_t		life;
  int			nb;
  t_state		state;
  int			chopstick;
  pthread_mutex_t	m_chopstick;
  int			rice;
  char			*name;
  struct s_philo	*r;
  struct s_philo	*l;
  int			clock;
  struct s_allin	*grp;
}			t_philo;

typedef struct		s_allin
{
  t_philo		*philos;
  t_bool		go_out;
  SDL_Rect		background_pos;
  SDL_Surface		*screen;
  SDL_Surface		*imageDeFond;
  SDL_Surface		*texte;
  Mix_Music		*music;
  pthread_t		event;
  int			nb_philo;
  int			rice_qty;
  TTF_Font		*police;
  SDL_Color		color;
}			t_allin;

void	*make_them_work(void *);
void	*display_state(void *);
void	display_activity(t_state);
void	display_philosopher(t_philo *);
int	init_sound(t_allin *);
void	init_font(t_allin *);
void	intro_screen(t_allin *);

#endif		/* !PHILOSOPHERS_H_ */
