/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:24:50 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/05 23:10:13 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int manage_philosophers(t_table *table, t_philo_list *philo_list, 
		t_fork_list *fork_list)
{
	
}


static int	philosophers_startup(int ac, char **av)
{
	t_table			*philo_table;
	t_philo_list	*philo_list;
	t_fork_list		*fork_list;
	int				return_status;

	if (!invalid_arg(ac, av))
		return (EXIT_FAILURE);
	philo_table = init_table(ac, av);
	if (philo_table)
		return (EXIT_FAILURE);
	fork_list = fork_list_init(philo_table);
	if (!fork_list)
		return (unit_table(philo_table), EXIT_FAILURE);
	philo_list = philosophers_list_init(philo_table, fork_list);
	if (!philo_list)
		return (unit_table(philo_table), unit_fork_list(fork_list), EXIT_FAILURE);
	return_status = manage_philosophers(philo_table, philo_list, fork_list);
	unit(fork_list, philo_list, philo_table);
	return (return_status);
}

int	main(int ac, char **av)
{
	if (!((ac == 5) ^ (ac == 6)))
		return (error_handler(WRONG_EXEC));
	else
		return (philosohpers_startup(ac, av));
}
