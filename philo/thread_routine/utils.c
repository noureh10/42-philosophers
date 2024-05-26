/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:10:25 by nechaara          #+#    #+#             */
/*   Updated: 2024/05/23 21:29:26 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	set_dead_philo(t_table *table, size_t index_of_philo, bool stopsim)
{
	if (!table)
		return ;
	if (stopsim)
	{
		pthread_mutex_lock(&table->table);
		table->is_sim_finished = true;
		pthread_mutex_unlock(&table->table);
	}
	else
	{
		pthread_mutex_lock(&table->table);
		table->philo[index_of_philo].is_dead = true;
		pthread_mutex_unlock(&table->table);
	}
}

static void	print_death(t_table *table, size_t philo_index)
{
	printf("%d %ld %s\n", get_time(table), philo_index, DEAD_M);
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
	pthread_mutex_lock(&table->table);
	if (table->is_sim_finished)
		return (true);
	while (index < table->data.number_of_philos)
	{
		if (table->philo[index].is_dead)
		{
			pthread_mutex_unlock(&table->table);
			return (true);
		}
		index++;
	}
	pthread_mutex_unlock(&table->table);
	return (false);
}

bool	check_hunger(t_table *table)
{
	size_t	index;

	if (!table)
		return (false);
	if (table->is_sim_finished)
		return (true);
	if (table->data.num_of_meals == NO_EAT_LIMIT)
		return (false);
	index = 0;
	while (index < table->data.number_of_philos)
	{
		if (table->philo[index].num_of_meals != table->data.num_of_meals)
			return (false);
		index++;
	}
	set_dead_philo(table, 0, true);
	return (true);
}
