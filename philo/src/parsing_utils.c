/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara.student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:36:14 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/16 16:27:12 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

size_t	ft_strlen(char *str)
{
	size_t	index;

	index = 0;
	if (!str)
		return (-1);
	while(str[index])
		index++;
	return (index);
}

int	ft_is_string_number(char *str)
{
	int	i;
	int	sign_count;

	i = 0;
	sign_count = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
		{
			sign_count++;
			if (i > 0)
				return (0);
		}
		else if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	if (ft_strlen(str) == 1 && sign_count == 1)
		return (0);
	return (1);
}

static void apply_bounds(t_bound *min, t_bound *max)
{
	min->number_of_philos = NUMBER_OF_PHILOS_MIN;
	min->time_to_die = TIME_TO_DIE_MIN;
	min->time_to_eat = TIME_TO_EAT_MIN;
	min->time_to_sleep = TIME_TO_SLEEP_MIN;
	max->number_of_philos = NUMBER_OF_PHILOS_MAX;
	max->time_to_die = TIME_TO_DIE_MAX;
	max->time_to_eat = TIME_TO_EAT_MAX;
	max->time_to_sleep = TIME_TO_SLEEP_MAX;
}

void apply_limits(t_limits *limit)
{
	apply_bounds(&limit->arg_min, &limit->arg_max);
}