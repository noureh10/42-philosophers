/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:08:59 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/03 00:40:41 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	real_time(void)
{
	int				time;
	struct timeval	time_value;

	gettimeofday(&time_value, NULL);
	time = (time_value.tv_sec * 1000 + time_value.tv_usec / 1000);
	return (time);
}

int	get_time(t_table *table)
{
	int	current_time;

	if (!table)
		return (NULL_PARAMS);
	current_time = real_time() - table->start_time;
	return (current_time);
}

void	ft_usleep(t_table *table, int time)
{
	int	start;

	if (!table)
		return ;
	start = get_time(table);
	while (get_time(table) < start + time)
		usleep(500);
}
