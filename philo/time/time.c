/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:08:59 by nechaara          #+#    #+#             */
/*   Updated: 2024/05/30 16:25:02 by nechaara         ###   ########.fr       */
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
	pthread_mutex_lock(&table->time);
	current_time = real_time() - table->start_time;
	pthread_mutex_unlock(&table->time);
	return (current_time);
}

void	ft_usleep(t_table *table, int time)
{
	int	start;

	start = get_time(table);
	while (get_time(table) < start + time)
		usleep(500);
}
