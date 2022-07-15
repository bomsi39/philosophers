/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:34:00 by dfranke           #+#    #+#             */
/*   Updated: 2022/07/15 10:40:23 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_death(t_prop *dat)
{
	pthread_mutex_lock(&dat->death_lock);
	if (dat->dead)
	{
		pthread_mutex_unlock(&dat->death_lock);
		return (true);
	}
	pthread_mutex_unlock(&dat->death_lock);
	return (false);
}

/*
Checks if a death happened. If yes, check_death returns true.
*/

bool	check_meals(t_prop *dat)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&dat->meal_lock);
	if (dat->meals_must_eat < 0)
	{
		pthread_mutex_unlock(&dat->meal_lock);
		return (false);
	}
	while (++i < dat->ph_no)
	{
		if (dat->meals_must_eat > dat->philos[i].finished_meals)
		{
			pthread_mutex_unlock(&dat->meal_lock);
			return (false);
		}
	}
	pthread_mutex_unlock(&dat->meal_lock);
	return (true);
}

/*
Checks every philo, if he reaches the desired amount of meals.
If one philo doesn't match the requirement, check_meals returns false.
*/

bool	check_meal_death(t_prop *dat)
{
	if (!check_death(dat) && !check_meals(dat))
		return (false);
	else
		return (true);
}
