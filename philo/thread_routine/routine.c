/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:51:12 by nechaara          #+#    #+#             */
/*   Updated: 2024/05/23 21:28:29 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*routine_loop(t_table *table, size_t philo, size_t left_philo)
{
	while (!check_hunger(table))
	{
		if (table->data.number_of_philos != 1)
		{
			philo_fork(table, philo, left_philo);
			philo_eat(table, philo, left_philo);
			if (table->philo[philo].num_of_meals == table->data.num_of_meals)
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
 * @param args 
 * @return void* 
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
	table->philo[current_philo].last_meal = get_time(table);
	if (table->philo[current_philo].philosophers_id % 2 == 0)
		ft_usleep(table, table->data.time_to_eat / MS_TRESHOLD);
	routine_loop(table, current_philo, left_philosopher);
	return (NULL);
}

static void	*manager_loop(t_table *table)
{
	size_t		index;
	int			time;

	while (true)
	{
		index = 0;
		while (index < table->data.number_of_philos)
		{
			time = get_time(table);
			pthread_mutex_lock(&table->meal_time);
			if (time - table->philo[index].last_meal >= table->data.time_to_die)
			{
				status_printer(table, index, DEAD);
				pthread_mutex_unlock(&table->table);
				return (NULL);
			}
			pthread_mutex_unlock(&table->meal_time);
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
 * philosopher and the simulation ends.
 * @param args 
 * @return void* 
 */
void	*manager_philosophers(void *args)
{
	t_table	*table;

	table = (t_table *)args;
	if (!table)
		return (NULL);
	return (manager_loop(table));
}
