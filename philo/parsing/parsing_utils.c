/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:24:38 by nechaara          #+#    #+#             */
/*   Updated: 2024/05/22 15:55:33 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	ft_strlen(char *str)
{
	size_t	index;

	index = 0;
	if (!str)
		return (-1);
	while (str[index])
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

void	set_argv_value_to_struct(t_data *values, int ac, char **av)
{
	values->number_of_philos = ft_strtol(av[1], NULL, 10);
	values->time_to_die = ft_strtol(av[2], NULL, 10);
	values->time_to_eat = ft_strtol(av[3], NULL, 10);
	values->time_to_sleep = ft_strtol(av[4], NULL, 10);
	if (ac == 6)
		values->num_of_meals = ft_strtol(av[5], NULL, 10);
}
