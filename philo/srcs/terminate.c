/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:22:34 by dfranke           #+#    #+#             */
/*   Updated: 2022/07/13 22:06:56 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	terminate(int error)
{
	if (error == 1)
	{
		write(1, "Error: philo input needs 4 or 5 arguments\n", 42);
		write(1, "1 -> number_of_philosophers\n", 28);
		write(1, "2 -> time_to_die\n", 17);
		write(1, "3 -> time_to_eat\n", 17);
		write(1, "4 -> time_to_sleep\n", 19);
		write(1, "optional:\n", 10);
		write(1, "5 -> number_of_times_each_philosopher_must_eat\n", 48);
	}
	else if (error == 2)
		write(1, "Error: only positive integers are accepted as input\n", 52);
	exit(0);
}

/*
Error message & exit management for wrong input
*/

void	dest_mut_free(t_prop *dat)
{
	int	i;

	i = -1;
	if (dat->ph_no == 1)
		pthread_mutex_unlock(&dat->forks[0]);
	while (++i < dat->ph_no)
		pthread_mutex_destroy(&dat->forks[i]);
	pthread_mutex_destroy(&dat->death_lock);
	pthread_mutex_destroy(&dat->meal_lock);
	pthread_mutex_destroy(&dat->write_lock);
	pthread_mutex_destroy(&dat->read_time);
	free(dat->philos);
	free(dat->forks);
}

/* 
Mutex unlock & -destruction and finally freeing of allocated memory space.
*/