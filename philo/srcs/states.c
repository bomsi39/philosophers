/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:17:28 by dfranke           #+#    #+#             */
/*   Updated: 2022/07/12 23:50:41 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_state(int event, t_philo *philo)
{
	time_t	time;

	pthread_mutex_lock(&philo->dat->write_lock);
	pthread_mutex_lock(&philo->dat->read_time);
	time = time_ms() - philo->dat->time_at_start;
	pthread_mutex_unlock(&philo->dat->read_time);
	if (event == 1 && 0 <= time && !(check_death(philo->dat)))
		printf("%ld\t%d has taken a fork\n", time, philo->id);
	else if (event == 2 && 0 <= time && !(check_death(philo->dat)))
		printf("%ld\t%d is eating\n", time, philo->id);
	else if (event == 3 && 0 <= time && !(check_death(philo->dat)))
		printf("%ld\t%d is sleeping\n", time, philo->id);
	else if (event == 4 && 0 <= time && !(check_death(philo->dat)))
		printf("%ld\t%d is thinking\n", time, philo->id);
	else if (event == 5 && 0 <= time)
		printf("%ld\t%d died\n", time, philo->id);
	pthread_mutex_unlock(&philo->dat->write_lock);
}

void	sleep_think(t_philo *philo)
{
	write_state(3, philo);
	sleep_good(philo->dat->tts, philo->dat);
	write_state(4, philo);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->dat->forks[philo->l_fo]);
	write_state(1, philo);
	if (philo->r_fo == philo->l_fo)
	{
		usleep(1000 * philo->dat->ttd);
		return ;
	}
	pthread_mutex_lock(&philo->dat->forks[philo->r_fo]);
	write_state(1, philo);
	write_state(2, philo);
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
