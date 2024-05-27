/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara.student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:16:57 by nechaara          #+#    #+#             */
/*   Updated: 2024/05/27 18:50:30 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	condition_checker(t_limits *limits, int ac, char **av)
{
	t_data	val;

	set_argv_value_to_struct(&val, ac, av);
	if (limits->arg_max.number_of_philos < val.number_of_philos
		|| limits->arg_min.number_of_philos > val.number_of_philos)
		return (!error_handler(WR_NUM_OF_PHIL));
	else if (limits->arg_max.time_to_die < val.time_to_die
		|| limits->arg_min.time_to_die > val.time_to_die)
		return (!error_handler(WR_TIME_TO_DIE));
	else if (limits->arg_max.time_to_eat < val.time_to_eat
		|| limits->arg_min.time_to_eat > val.time_to_eat)
		return (!error_handler(WR_TIME_TO_EAT));
	else if (limits->arg_max.time_to_sleep < val.time_to_sleep
		|| limits->arg_min.time_to_sleep > val.time_to_sleep)
		return (!error_handler(WR_TIME_TO_SLEEP));
	if (ac == 6)
		if (limits->arg_max.num_of_meals < val.num_of_meals)
			return (!error_handler(WR_NUM_OF_MEALS));
	return (true);
}

static void	apply_bounds(t_data *min, t_data *max)
{
	min->number_of_philos = NUMBER_OF_PHILOS_MIN;
	min->time_to_die = TIME_TO_DIE_MIN;
	min->time_to_eat = TIME_TO_EAT_MIN;
	min->time_to_sleep = TIME_TO_SLEEP_MIN;
	min->num_of_meals = NUMBER_OF_REQUIRED_MEALS_MIN;
	max->number_of_philos = NUMBER_OF_PHILOS_MAX;
	max->time_to_die = TIME_TO_DIE_MAX;
	max->time_to_eat = TIME_TO_EAT_MAX;
	max->time_to_sleep = TIME_TO_SLEEP_MAX;
	max->num_of_meals = NUMBER_OF_REQUIRED_MEALS_MAX;
}

void	apply_limits(t_limits *limit)
{
	apply_bounds(&limit->arg_min, &limit->arg_max);
}

bool	invalid_arg(int ac, char **av)
{
	t_limits	limit;
	size_t		index;

	index = 1;
	while (av[index])
		if (!ft_is_string_number(av[index++]))
			return (true);
	apply_limits(&limit);
	if (condition_checker(&limit, ac, av))
		return (true);
	return (false);
}
