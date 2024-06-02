/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:51:07 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/03 00:58:28 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_left_philosopher(t_table *table, size_t current_philo)
{
	size_t	value;

	if (!table)
		return (NULL_PARAMS);
	else if (current_philo == 0)
		value = table->data.number_of_philos - 1;
	else
		value = current_philo - 1;
	return (value);
}

void	philo_eat(t_table *table, size_t current_philo, size_t left_philo)
{
	status_printer(table, current_philo, EAT);
	pthread_mutex_lock(&table->meal_time);
	table->philo[current_philo].last_meal = get_time(table);
	table->philo[current_philo].num_of_meals++;
	pthread_mutex_unlock(&table->meal_time);
	ft_usleep(table, table->data.time_to_eat);
	pthread_mutex_unlock(&table->philo[current_philo].fork);
	pthread_mutex_unlock(&table->philo[left_philo].fork);
}

void	philo_fork(t_table *table, size_t current_philo, size_t left_philo)
{
	pthread_mutex_lock(&table->philo[current_philo].fork);
	status_printer(table, current_philo, FORK);
	pthread_mutex_lock(&table->philo[left_philo].fork);
	status_printer(table, current_philo, FORK);
}

void	philo_sleep(t_table *table, size_t current_philo)
{
	if (!table)
		return ;
	status_printer(table, current_philo, SLEEP);
	ft_usleep(table, table->data.time_to_sleep);
}
