/*
** philosophers.h for Philosophes in /home/paasch_j/rendu/PSU_2014_philo/include
**
** Made by Johan Paasche
** Login   <paasch_j@epitech.net>
**
** Started on  Tue Feb 17 01:13:05 2015 Johan Paasche
** Last update Sat Feb 21 19:44:39 2015 Johan Paasche
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

# define	NB_PHILO	(12)

/*
** Let's introduce a quik funy rule while stopping the game if RICE (X) falls to 0.
*/

# define	RICE		(200)

/*
**	Just for paasch_j
*/

# define	INFINITE_LOOP	(42)


# define	ACTION_TIME	(1)
/*
**	Global mutex are representing the chopsticks
*/

pthread_mutex_t		g_chopstick[NB_PHILO];

/*
** Code cleaner, code smarter
*/

typedef	char t_bool;

# define	TRUE	(1)
# define	FALSE	(0)

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
  t_state		activity;
  int			chopstick;
  t_bool		restored;
  int			rice;
  char			*name;
  struct s_philo	*r;	/* finalement on va bien avoir besoin des voisins */
  struct s_philo	*l;	/* pour connaitre leur etats j'avais pas bien lu le sujet */
  int			clock;	/* Pour les durées maximales d'actions */
}			t_philo;

void	*make_them_work(void *);

void	*display_state(void *);
void	display_activity(t_state);
void	display_philosopher(t_philo *);

#endif		/* !PHILOSOPHERS_H_ */
