/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_unit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:09:55 by nechaara          #+#    #+#             */
/*   Updated: 2024/05/23 21:27:59 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief 
 * The init function initialize everything needed to make the dinning simulation
 * possible. It will initialize all the philos, then it initializes mutexes that
 * are needed to synchronize all the threads and prevent data-race. It returns
 * a boolean based on wheter or not it has successfully initialized the table.
 * @param table The reference of the table we will initialize.
 */
bool	init_table(t_table *table)
{
	size_t	i;
	t_philo	*current_working_philo;

	if (!table)
		return (false);
	table->philo = malloc(sizeof(t_philo) * table->data.number_of_philos);
	if (!table->philo)
		return (false);
	i = 0;
	current_working_philo = table->philo;
	while (i < table->data.number_of_philos)
	{
		current_working_philo->philosophers_id = i + 1;
		current_working_philo->is_dead = false;
		current_working_philo->num_of_meals = 0;
		current_working_philo->last_meal = 0;
		pthread_mutex_init(&current_working_philo->fork, NULL);
		current_working_philo++;
		i++;
	}
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->table, NULL);
	pthread_mutex_init(&table->meal_time, NULL);
	pthread_mutex_init(&table->time, NULL);
	return (true);
}

/**
 * @brief The set routine args function has one purpose, to return
 * args that will be used in the routine function of each philo.
 * It needs the table for context
 * @param table The working table.
 * @return t_routine_args* The args that will be passed in the thread function.
 */
t_routine_args	*set_routine_args(t_table *table)
{
	size_t			i;
	size_t			malloc_size;
	t_routine_args	*routine_args;

	if (!table)
		return (NULL);
	malloc_size = (sizeof(t_routine_args) * table->data.number_of_philos);
	routine_args = (t_routine_args *)malloc(malloc_size);
	if (!routine_args)
		return (NULL);
	i = 0;
	while (i < table->data.number_of_philos)
	{
		routine_args[i].table = table;
		routine_args[i].index = i;
		i++;
	}
	return (routine_args);
}

void	unit_table(t_table *table)
{
	if (!table)
		return ;
	pthread_mutex_destroy(&table->meal_time);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->table);
	pthread_mutex_destroy(&table->time);
	free(table->philo);
}

bool	parsing_data(t_table *table, int ac, char **av)
{
	if (!table || !av || ac < 0)
		return (false);
	table->data.number_of_philos = ft_strtol(av[1], NULL, 10);
	table->data.time_to_die = ft_strtol(av[2], NULL, 10);
	table->data.time_to_eat = ft_strtol(av[3], NULL, 10);
	table->data.time_to_sleep = ft_strtol(av[4], NULL, 10);
	if (av[5])
		table->data.num_of_meals = ft_strtol(av[5], NULL, 10);
	else
		table->data.num_of_meals = NO_EAT_LIMIT;
	table->is_sim_finished = false;
	table->start_time = 0;
	table->philo = NULL;
	return (true);
}
