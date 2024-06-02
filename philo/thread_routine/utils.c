/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:10:25 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/03 01:03:28 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	set_dead_philo(t_table *table, size_t index_of_philo, bool stopsim)
{
	if (!table)
		return ;
	pthread_mutex_lock(&table->death_mtx);
	if (stopsim)
		table->is_sim_finished = true;
	else
		table->philo[index_of_philo].is_dead = true;
	pthread_mutex_unlock(&table->death_mtx);
}

static void	print_death(t_table *table, size_t philo_index)
{
	printf("%d %ld %s\n", get_time(table), philo_index + 1, DEAD_M);
	set_dead_philo(table, philo_index, true);
}

/**
 * @brief 
 * The status printer functions outputs the current action of the current philo
 * aka philo_index. We block this code section with a mutex to avoid data race.
 * @param table The table we're working on.
 * @param philo_index The current philo.
 * @param print_code The print code.
 */
void	status_printer(t_table *table, size_t philo_index, int print_code)
{
	if (!table)
		return ;
	pthread_mutex_lock(&table->print);
	if (!check_hunger(table))
	{
		if (print_code == FORK)
			printf("%d %ld %s\n", get_time(table), philo_index + 1, FORK_M);
		else if (print_code == EAT)
			printf("%d %ld %s\n", get_time(table), philo_index + 1, EAT_M);
		else if (print_code == SLEEP)
			printf("%d %ld %s\n", get_time(table), philo_index + 1, SLEEP_M);
		else if (print_code == THINK)
			printf("%d %ld %s\n", get_time(table), philo_index + 1, THINK_M);
		else if (print_code == DEAD)
			print_death(table, philo_index);
	}
	pthread_mutex_unlock(&table->print);
}

bool	has_died(t_table *table)
{
	size_t	index;

	if (!table)
		return (true);
	index = 0;
	if (table->is_sim_finished)
		return (true);
	while (index < table->data.number_of_philos)
	{
		pthread_mutex_lock(&table->philo[index].death_lock);
		if (table->philo[index].is_dead)
		{
			pthread_mutex_unlock(&table->philo[index].death_lock);
			return (true);
		}
		index++;
		pthread_mutex_unlock(&table->philo[index].death_lock);
	}
	return (false);
}

bool	check_hunger(t_table *table)
{
	size_t	index;
	size_t	num_of_meals;

	if (!table)
		return (false);
	pthread_mutex_lock(&table->death_mtx);
	if (table->is_sim_finished)
		return (pthread_mutex_unlock(&table->death_mtx), true);
	pthread_mutex_unlock(&table->death_mtx);
	if (table->data.num_of_meals < 0)
		return (false);
	index = 0;
	num_of_meals = (size_t) table->data.num_of_meals;
	while (index < table->data.number_of_philos)
	{
		pthread_mutex_lock(&table->meal_time);
		if (table->philo[index].num_of_meals != num_of_meals)
			return (pthread_mutex_unlock(&table->meal_time), false);
		pthread_mutex_unlock(&table->meal_time);
		index++;
	}
	set_dead_philo(table, 0, true);
	return (true);
}
