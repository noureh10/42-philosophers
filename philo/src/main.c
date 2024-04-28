/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara.student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:24:50 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/28 19:20:35 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// TODO : Need to figure out how to manage time on each philosophers

static	t_routine generate_routine(t_table *table, t_philo *current_philo)
{
	t_routine routine;
	
	routine.table = table;
	routine.current_philosopher = current_philo;
	return (routine);
}

static int manage_philosophers(t_table *table, t_philo_list *philo_list, 
		t_fork_list *fork_list)
{
	t_philo_list	*temp_head_philo;
	t_fork_list		*temp_head_fork;
	t_routine		routine;
	int				actual_time;

	if (!table || !philo_list || !fork_list)
		return (-1);
	temp_head_philo = philo_list;
	temp_head_fork = fork_list;
	while (temp_head_philo)
	{
		routine = generate_routine(table, temp_head_philo->content);
		pthread_create(&temp_head_philo->content->philo, NULL, thread_routine, &routine);
		temp_head_philo = temp_head_philo->next;
		ft_usleep(10);
	}
	table->starting_time = get_time();
	while (!table->finished_sim)
	{
		actual_time = get_time() - table->starting_time;
		check_state_of_philos(actual_time, philo_list);
		ft_usleep(10);
	}
	return (0);
}

// temporary (debug)
static void check_philo_and_fork_list(t_philo_list *philo_list, t_fork_list *fork_list)
{
	while (philo_list)
	{
		printf("PHILO ID : %zu\n", philo_list->content->philosophers_id);
		philo_list = philo_list->next;
	}
	while (fork_list)
	{
		printf("FORK ID : %zu\n", fork_list->content->fork_id);
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
	fork_list = fork_list_init(philo_table);
	if (!fork_list)
		return (unit_table(philo_table), EXIT_FAILURE);
	philo_list = philosophers_list_init(philo_table, fork_list);
	if (!philo_list)
		return (unit_table(philo_table), unit_fork_list(fork_list), EXIT_FAILURE);
	check_philo_and_fork_list(philo_list, fork_list);
	philo_table->start_dining = true;
	return_status = manage_philosophers(philo_table, philo_list, fork_list);
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
