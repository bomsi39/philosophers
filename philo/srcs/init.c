/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:06:34 by dfranke           #+#    #+#             */
/*   Updated: 2022/07/15 10:30:42 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_prop *dat)
{
	pthread_mutex_t	*forks;
	int				nbr;

	nbr = dat->ph_no;
	forks = malloc(sizeof(pthread_mutex_t) * nbr);
	while (nbr--)
		pthread_mutex_init(&forks[nbr], NULL);
	pthread_mutex_init(&dat->write_lock, NULL);
	pthread_mutex_init(&dat->read_time, NULL);
	pthread_mutex_init(&dat->meal_lock, NULL);
	pthread_mutex_init(&dat->death_lock, NULL);
	dat->forks = forks;
}

/*
Initialises one mutex for every fork and all other necessary mutexes.
*/

void	init_philos(t_prop *dat)
{
	int			i;
	t_philo		*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * dat->ph_no);
	while (i < dat->ph_no)
	{
		philo[i].idx = i;
		philo[i].id = i + 1;
		philo[i].finished_meals = 0;
		philo[i].l_fo = i;
		philo[i].r_fo = (i + 1) % dat->ph_no;
		philo[i].dat = dat;
		i++;
	}
	dat->philos = philo;
}

/*
Initialises all required philos with all attributes.
*/