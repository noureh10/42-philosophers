/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:02:34 by nechaara          #+#    #+#             */
/*   Updated: 2024/06/02 15:23:10 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	error_handler(char *message)
{
	printf("%s\n", message);
	return (EXIT_FAILURE);
}

static bool	philo_stop(t_table *table, t_routine_args *args, pthread_t manager)
{
	size_t	index;
	int		status;

	if (!table)
		return (false);
	index = 0;
	status = 0;
	while (index < table->data.number_of_philos)
	{
		status = pthread_join(table->philo[index].philo_thread, NULL);
		if (status != 0)
			return (free(args), false);
		index++;
	}
	status = pthread_join(manager, NULL);
	if (status != 0)
		return (free(args), false);
	free(args);
	return (true);
}

bool	philo_thread_startup(t_table *table)
{
	t_routine_args		*routine_args;
	size_t				index;
	pthread_t			manager;
	int					status;

	routine_args = set_routine_args(table);
	table->start_time = real_time();
	if (!routine_args)
		return (false);
	status = 1;
	index = 0;
	while (index < table->data.number_of_philos)
	{
		status = pthread_create(&table->philo[index].philo_thread, NULL, \
			&routine, &routine_args[index]);
		if (status != 0)
			return (free(routine_args), false);
		index++;
	}
	status = pthread_create(&manager, NULL, &manager_philosophers, table);
	if (status != 0)
		return (free(routine_args), false);
	philo_stop(table, routine_args, manager);
	return (true);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (!((ac == 5) ^ (ac == 6)))
		return (error_handler(WRONG_EXEC));
	else if (invalid_arg(ac, av))
		return (EXIT_FAILURE);
	else if (!parsing_data(&table, ac, av))
		return (EXIT_FAILURE);
	else if (!init_table(&table))
		return (EXIT_FAILURE);
	if (philo_thread_startup(&table))
		return (unit_table(&table), EXIT_FAILURE);
	unit_table(&table);
	return (EXIT_SUCCESS);
}
