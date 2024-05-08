/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:52:03 by nechaara          #+#    #+#             */
/*   Updated: 2024/05/08 16:57:19 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	get_time(void)
{
	long			time;
	struct	timeval	time_value;

	gettimeofday(&time_value, NULL);
	time = (time_value.tv_sec * 1000 + time_value.tv_usec / 1000);
	return (time);
}

long		get_relative_time(t_table *table)
{
	long	current_time;
	
	if (!table)
		return (-1);
	pthread_mutex_lock(&table->time);
	current_time = get_time() - table->start_time;
	pthread_mutex_unlock(&table->time);
	return (current_time);
}

void	ft_usleep(t_table *table, int time)
{
	int	start;

	start = get_time();
	while (get_relative_time(table) < start + time)
		usleep(500);
}
