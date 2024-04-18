/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:24:50 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/17 15:28:25 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"


static int manage_philosophers(t_table *table, t_philo_list *philo_list, 
		t_fork_list *fork_list)
{
	return (1);
}

// temporary (debug)
static void check_philo_and_fork_list(t_philo_list *philo_list, t_fork_list *fork_list)
{
	while (philo_list)
	{
		printf("PHILO ID : %d\n", philo_list->content->philosophers_id);
		philo_list = philo_list->next;
	}
	while (fork_list)
	{
		printf("FORK ID : %d\n", fork_list->content->fork_id);
		fork_list = fork_list->next;
	}
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
	if (!philo_table)
		return (EXIT_FAILURE);
	fork_list_init(philo_table, &fork_list);
	if (!fork_list)
		return (unit_table(philo_table), EXIT_FAILURE);
	philosophers_list_init(philo_table, fork_list, &philo_list);
	if (!philo_list)
		return (unit_table(philo_table), unit_fork_list(fork_list), EXIT_FAILURE);
	check_philo_and_fork_list(philo_list, fork_list);
	//return_status = manage_philosophers(philo_table, philo_list, fork_list);
	//unit(fork_list, philo_list, philo_table);
	return (return_status);
}

int	main(int ac, char **av)
{
	if (!((ac == 5) ^ (ac == 6)))
		return (error_handler(WRONG_EXEC));
	else
		return (philosophers_startup(ac, av));
}
