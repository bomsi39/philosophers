/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:14:18 by dfranke           #+#    #+#             */
/*   Updated: 2022/07/13 00:05:34 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_thread(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->idx % 2 == 1)
		usleep(1000);
	while (!check_death(philo->dat) && !check_meals(philo->dat))
	{
		eat(philo);
		sleep_think(philo);
	}
	return (0);
}

/*
Every philo "lives" through this thread. While no philo is dead nor
one philo didn't reach its necessary meal amount, every philo will eat,
sleep and think.
*/

void	*death_finder(void *arg)
{
	t_philo		*philo;
	int			i;
	long		time_diff;

	philo = (t_philo *)arg;
	while (!check_death(philo->dat) && !check_meals(philo->dat))
	{
		i = 0;
		while (i < philo->dat->ph_no)
		{
			pthread_mutex_lock(&philo->dat->read_time);
			time_diff = time_ms() - philo[i].last_meal;
			pthread_mutex_unlock(&philo->dat->read_time);
			if (time_diff > philo->dat->ttd)
			{
				write_state(5, philo);
				pthread_mutex_lock(&philo->dat->death_lock);
				philo->dat->dead = true;
				pthread_mutex_unlock(&philo->dat->death_lock);
				break ;
			}
			i++;
		}
	}
	return (0);
}

/* 
This thread checks constantly if time_to_die from every philo is exceeded.
If thats the case, the variable philo->dat->dead is set to true.
*/

void	create_philos(t_prop *dat)
{
	int			i;
	pthread_t	*thread;
	pthread_t	status;

	thread = malloc(sizeof(pthread_t) * dat->ph_no);
	dat->time_at_start = time_ms();
	i = -1;
	while (++i < dat->ph_no)
	{
		pthread_create(&thread[i], NULL, &philo_thread,
			(void *)&dat->philos[i]);
		pthread_mutex_lock(&dat->read_time);
		dat->philos[i].last_meal = time_ms();
		pthread_mutex_unlock(&dat->read_time);
	}
	pthread_create(&status, NULL, &death_finder, (void *)dat->philos);
	pthread_join(status, NULL);
	i = -1;
	while (++i < dat->ph_no)
		pthread_join(thread[i], NULL);
	free(thread);
}

/*
In this function a thread for every philo is being created. 
After the creation is finished an ohter thread (status) is created.
Its Purpose is to constantly monitor the times of every philo.
*/