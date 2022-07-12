/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:03:06 by dfranke           #+#    #+#             */
/*   Updated: 2022/07/12 23:50:23 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>

struct	s_prop;

typedef struct s_philos
{
	int					idx;
	int					id;
	int					total_philos;
	int					finished_meals;
	int					meals_must_eat;
	int					tte;
	int					tts;
	int					ttd;
	long				last_meal;
	int					l_fo;
	int					r_fo;
	struct s_prop		*dat;
}	t_philo;

typedef struct s_prop
{
	int				ph_no;
	int				tte;
	int				tts;
	int				ttd;
	bool			dead;
	int				meals_must_eat;
	time_t			time_at_start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	read_time;
	pthread_t		status;
	t_philo			*philos;
}	t_prop;

/* Init */
void	init_mutexes(t_prop *dat);
void	init_philos(t_prop *dat);

/* Threads */
void	create_philos(t_prop *dat);
bool	check_death(t_prop *dat);
bool	check_meals(t_prop *dat);

/* States */
void	eat(t_philo *philo);
void	sleep_think(t_philo *philo);
void	write_state(int event, t_philo *philo);

/* Terminate & Free */
void	terminate(int error);
void	dest_mut_free(t_prop *dat);

/* Utils */
long	ft_atol(const char *str);
bool	ft_isstrnum(char *str);
void	sleep_good(int time, t_prop *dat);
time_t	time_ms(void);

#endif