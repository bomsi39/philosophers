/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:20:20 by dfranke           #+#    #+#             */
/*   Updated: 2022/07/13 00:07:37 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

/*
Converts ascii to long (just positive)
*/

bool	ft_isstrnum(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '+' || str[i] == '0')
	{
		i++;
		if (str[i] == '\0')
			return (false);
	}
	while (str[i])
	{
		if (str[i] < '0' || '9' < str[i])
			return (false);
		i++;
	}
	return (true);
}

/*
checks if str is a positive number
*/

void	sleep_good(int time, t_prop *dat)
{
	time_t	i;

	i = time_ms();
	while (!check_death(dat))
	{
		if (time_ms() - i >= time)
			break ;
		usleep(50);
	}
}



time_t	time_ms(void)
{
	struct timeval	time_is;
	time_t			time;

	time = 0;
	gettimeofday(&time_is, NULL);
	time = (time_is.tv_sec * 1000) + (time_is.tv_usec / 1000);
	return (time);
}
