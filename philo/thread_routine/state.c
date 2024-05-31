/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:51:07 by nechaara          #+#    #+#             */
/*   Updated: 2024/05/30 23:03:08 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	param_checker(t_table *table, size_t current_philo)
{
	if (!table)
		return (false);
	else if (current_philo > table->data.number_of_philos)
		return (false);
	return (true);
}

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
	if (!param_checker(table, current_philo))
		return ;
	status_printer(table, current_philo, EAT);
	pthread_mutex_lock(&table->meal_time);
	table->philo[current_philo].last_meal = get_time(table);
	table->philo[current_philo].num_of_meals++;
	pthread_mutex_unlock(&table->meal_time);
	ft_usleep(table, table->data.time_to_eat);
	pthread_mutex_unlock(&table->philo[left_philo].fork);
	pthread_mutex_unlock(&table->philo[current_philo].fork);
}

/**
 * @brief 
 * This function locks the fork mutexes of the current philosopher and the left
 * philosophers. We ensure that a philosopher pick up the fork in a consistent
 * order to prevent lock order inversion, thus avoiding potential deadlocks.
 * @param table Pointer to the table structure.
 * @param current_philo Index of current philo.
 * @param left_philo Index of the left philo.
 */
void	philo_fork(t_table *table, size_t current_philo, size_t left_philo)
{
	size_t	first_fork;
	size_t	second_fork;

	if (!param_checker(table, current_philo))
		return ;
	if (current_philo < left_philo)
	{
		first_fork = current_philo;
		second_fork = left_philo;
	}
	else
	{
		first_fork = left_philo;
		second_fork = current_philo;
	}
	pthread_mutex_lock(&table->philo[first_fork].fork);
	status_printer(table, current_philo, FORK);
	pthread_mutex_lock(&table->philo[second_fork].fork);
	status_printer(table, current_philo, FORK);
}

void	philo_sleep(t_table *table, size_t current_philo)
{
	if (!param_checker(table, current_philo))
		return ;
	status_printer(table, current_philo, SLEEP);
	ft_usleep(table, table->data.time_to_sleep);
}
