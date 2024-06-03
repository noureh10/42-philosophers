/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara.student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:51:12 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/03 13:46:15 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*routine_loop(t_table *table, size_t philo, size_t left_philo)
{
	size_t	num_of_meals;

	num_of_meals = (size_t) table->data.num_of_meals;
	while (!check_hunger(table))
	{
		if (table->data.number_of_philos != 1)
		{
			philo_fork(table, philo, left_philo);
			philo_eat(table, philo, left_philo);
			if (table->philo[philo].num_of_meals == num_of_meals)
				return (NULL);
		}
		philo_sleep(table, philo);
		status_printer(table, philo, THINK);
	}
	return (NULL);
}

/**
 * @brief 
 * The routine function binds with each created thread exept for the manager
 * thread. It casts the void * args to routine_args, a structure that contain
 * relevant data for the simulation to be successful (the index of the philo
 * and the reference of the table). We make it sure put a delay on each even
 * philosopher so each philo doesn't try to access the concurent fork on the
 * left. The routine will stop if the simulation is finished or the hunger
 * count is achieved.
 * @param args The routine args containing the reference of the table and
 * the index of the philo.
 */
void	*routine(void *args)
{
	t_routine_args	*routine_args;
	size_t			current_philo;
	size_t			left_philosopher;
	t_table			*table;

	routine_args = (t_routine_args *)args;
	if (!routine_args)
		return (NULL);
	current_philo = routine_args->index;
	table = routine_args->table;
	left_philosopher = get_left_philosopher(table, current_philo);
	pthread_mutex_lock(&table->time);
	table->philo[current_philo].last_meal = get_time(table);
	pthread_mutex_unlock(&table->time);
	if (table->philo[current_philo].philosophers_id % 2 == 0)
		ft_usleep(table, 10);
	routine_loop(table, current_philo, left_philosopher);
	return (NULL);
}

static void	*manager_loop(t_table *table)
{
	size_t		index;
	int			meal_diff;

	while (true)
	{
		index = 0;
		while (index < table->data.number_of_philos)
		{
			pthread_mutex_lock(&table->time);
			pthread_mutex_lock(&table->meal_time);
			meal_diff = get_time(table) - table->philo[index].last_meal;
			pthread_mutex_unlock(&table->meal_time);
			pthread_mutex_unlock(&table->time);
			if (meal_diff >= 0 && meal_diff >= (int) table->data.time_to_die)
				return (status_printer(table, index, DEAD), NULL);
			if (check_hunger(table))
				return (NULL);
			index++;
		}
	}
	return (NULL);
}

/**
 * @brief 
 * The manager_philosophers function binds to the manager thread. It has one
 * purpose, to check if one of the philosopher exceeded the time to die when
 * it comes to meals. If it did, the manager loop prints out the death of the
 * philosopher and the simulation ends. It will also end the simulation if
 * the number of meal is reached.
 * @param args A pointer of the table.
 */
void	*manager_philosophers(void *args)
{
	t_table	*table;

	table = (t_table *)args;
	if (!table)
		return (NULL);
	return (manager_loop(table));
}
