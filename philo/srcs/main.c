/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:38:50 by dfranke           #+#    #+#             */
/*   Updated: 2022/07/15 10:16:45 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || 6 < argc)
		terminate(1);
	while (i <= argc - 1)
	{
		if (!ft_isstrnum(argv[i]) || 2147483647 < ft_atol(argv[i++]))
			terminate(2);
	}
}

/* Checks if number of arguments is correct and if the arguments are 
positive integers */

void	parse_args(char **argv, t_prop *dat)
{
	dat->ph_no = ft_atol(argv[1]);
	dat->ttd = ft_atol(argv[2]);
	dat->tte = ft_atol(argv[3]);
	dat->tts = ft_atol(argv[4]);
	dat->meals_must_eat = -1;
	if (argv[5])
		dat->meals_must_eat = ft_atol(argv[5]);
	dat->dead = false;
}

/* User input gets parsed into struct */

int	main(int argc, char **argv)
{
	t_prop	dat;

	check_args(argc, argv);
	parse_args(argv, &dat);
	init_mutexes(&dat);
	init_philos(&dat);
	create_philos(&dat);
	dest_mut_free(&dat);
	return (0);
}
