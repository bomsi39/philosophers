/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:17:28 by dfranke           #+#    #+#             */
/*   Updated: 2022/07/15 12:21:08 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_state(int event, t_philo *philo)
{
	time_t	time;

	pthread_mutex_lock(&philo->dat->write_lock);
	time = time_ms() - philo->dat->time_at_start;
	if (event == frk && 0 <= time && !check_meal_death(philo->dat))
		printf("%ld\t%d has taken a fork\n", time, philo->id);
	else if (event == eats && 0 <= time && !check_meal_death(philo->dat))
		printf("%ld\t%d is eating\n", time, philo->id);
	else if (event == sleeps && 0 <= time && !check_meal_death(philo->dat))
		printf("%ld\t%d is sleeping\n", time, philo->id);
	else if (event == thinks && 0 <= time && !check_meal_death(philo->dat))
		printf("%ld\t%d is thinking\n", time, philo->id);
	else if (event == dies && 0 <= time)
		printf("%ld\t%d died\n", time, philo->id);
	pthread_mutex_unlock(&philo->dat->write_lock);
}

/*
Writes the state every philosopher is in, in the correct format.
*/

void	sleep_think(t_philo *philo)
{
	write_state(sleeps, philo);
	sleep_good(philo->dat->tts, philo->dat);
	write_state(thinks, philo);
}

/*
eat and think process
*/

void	take_forks(t_philo *philo)
{
	if (philo->idx % 2 == 0)
	{
		pthread_mutex_lock(&philo->dat->forks[philo->l_fo]);
		write_state(frk, philo);
	}
	if (philo->r_fo == philo->l_fo)
	{
		usleep(1000 * philo->dat->ttd);
		return ;
	}
	pthread_mutex_lock(&philo->dat->forks[philo->r_fo]);
	if (philo->idx % 2 == 1)
	{
		pthread_mutex_lock(&philo->dat->forks[philo->l_fo]);
		write_state(frk, philo);
	}
	write_state(frk, philo);
}

/*
Manages that philos with an odd number take the left fork first, then the right
fork and philos with an even number take the right fork first and then the left
*/

void	eat(t_philo *philo)
{
	take_forks(philo);
	write_state(eats, philo);
	pthread_mutex_lock(&philo->dat->read_time);
	philo->last_meal = time_ms();
	pthread_mutex_unlock(&philo->dat->read_time);
	sleep_good(philo->dat->tte, philo->dat);
	pthread_mutex_lock(&philo->dat->meal_lock);
	philo->finished_meals += 1;
	pthread_mutex_unlock(&philo->dat->meal_lock);
	pthread_mutex_unlock(&philo->dat->forks[philo->l_fo]);
	pthread_mutex_unlock(&philo->dat->forks[philo->r_fo]);
}

/*
Eating process of the philosopher, he takes both forks (mutexes), then starts 
to eat.
*/