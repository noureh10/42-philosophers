/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:44:57 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/11 15:55:33 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void set_argv_value_to_struct(t_bound *values, int ac, char **av)
{
	values->number_of_philos = ft_strtol(av[NUMBER_OF_PHILOS_INDEX], NULL, 10);
	values->time_to_die = ft_strtol(av[TIME_TO_DIE_INDEX], NULL, 10);
	values->time_to_eat = ft_strtol(av[TIME_TO_EAT_INDEX], NULL, 10);
	values->time_to_sleep = ft_strtol(av[TIME_TO_SLEEP_INDEX], NULL, 10);
}

static bool	condition_checker(t_limits *limits, int ac, char **av)
{
	t_bound values;
	
	set_argv_value_to_struct(&values, ac, av);
	if (!(limits->arg_max.number_of_philos < values.number_of_philos
		|| limits->arg_min.number_of_philos > values.number_of_philos
		|| limits->arg_max.time_to_die < values.time_to_die
		|| limits->arg_min.time_to_die > values.time_to_die
		|| limits->arg_max.time_to_eat < values.time_to_eat
		|| limits->arg_min.time_to_eat > values.time_to_eat
		|| limits->arg_max.time_to_sleep < values.time_to_sleep
		|| limits->arg_min.time_to_sleep > values.time_to_sleep))
			{
				printf("ici");
				return (false);
			}
	return (true);
}

bool	invalid_arg(int ac, char **av)
{
	t_limits limit;

	apply_limits(&limit);
	if (!condition_checker(&limit, ac, av))
		return (false);
	return (true);
}
