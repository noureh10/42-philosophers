/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:44:57 by nechaara          #+#    #+#             */
/*   Updated: 2024/03/26 18:23:18 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static size_t ft_strlen(char *str)
{
	size_t	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

static int     ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int ft_is_string_number(char *str)
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
		else if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (ft_strlen(str) == 1 && sign_count == 1)
		return (0);
	return (1);
}

static bool condition_checker(char *str, int minimum)
{
	int	temporary_value;

	temporary_value = ft_strtol(str, NULL, 10);
	if (temporary_value <= minimum)
		return (false);
	return (true);
}

// TODO : Need to find the minimum values to each one of the argv

bool  invalid_arg(int ac, char **av)
{
	size_t	index;
	int		min_argv_val[5];
	
	min_argv_val[NUMBER_OF_PHILOS_INDEX] = 0;
	min_argv_val[TIME_TO_DIE_INDEX] = 0;
	min_argv_val[TIME_TO_EAT_INDEX] = 0;
	min_argv_val[TIME_TO_SLEEP_INDEX] = 0;
	min_argv_val[EAT_LIMIT_INDEX] = 0;
	index = 1;
	while (av[index])
		if (!ft_is_string_number(av[index++]))
			return (false);
	index = 1;
	while (av[index])
		if (condition_checker(av[index++], min_argv_val[index - 1]))
			return (false);
	return (true);
}
