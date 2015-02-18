/*
** philosophers.h for Philosophes in /home/paasch_j/rendu/PSU_2014_philo/include
**
** Made by Johan Paasche
** Login   <paasch_j@epitech.net>
**
** Started on  Tue Feb 17 01:13:05 2015 Johan Paasche
** Last update Wed Feb 18 17:40:09 2015 Johan Paasche
*/

#ifndef		PHILOSOPHERS_H_
# define	PHILOSOPHERS_H_

# include	<unistd.h>
# include	<stdio.h>
# include	<pthread.h>
# include	<stdlib.h>

# define	UNUSED		__attribute__((unused))

/*
** Number of philosophers, influencing the number of mutexs we gonna have
*/

# define	NB_PHILO	(7)

/*
** Let's introduce a quik funy rule while stopping the game if RICE (X) falls to 0.
*/

# define	RICE		(15)

/*
**	Just for paasch_j
*/

# define	INFINITE_LOOP	42

/*
**	Global mutex are representing the chopsticks
*/

pthread_mutex_t		g_chopstick[NB_PHILO];

/*
** Code cleaner, code smarter
*/

typedef	char t_bool;

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
  t_state		activity;
  t_bool		chopstick;
  t_bool		restored;
  int			rice;
  char			*name;
}			t_philo;

void	*make_them_work(void *philos);

#endif		/* !PHILOSOPHERS_H_ */
