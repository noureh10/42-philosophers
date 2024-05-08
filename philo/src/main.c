/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:24:50 by nechaara          #+#    #+#             */
/*   Updated: 2024/05/08 16:58:57 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// TODO : Need to figure out how to manage time on each philosophers

static	t_routine_args generate_routine(t_table *table, t_philo *current_philo)
{
	t_routine_args routine;
	
	routine.table = table;
	routine.current_philosopher = current_philo;
	return (routine);
}

static void philo_checkup(int time,t_table *table, t_philo_list *philo_list)
{
	t_philo_list 	*temp_philo_list_head;
	unsigned int				actual_time;

	temp_philo_list_head = table->philo_list_head;
	while (true)
	{
		temp_philo_list_head = table->philo_list_head;
		while (temp_philo_list_head)
		{
			actual_time = get_time();
			pthread_mutex_lock(&temp_philo_list_head->content->data_lock);
			if (temp_philo_list_head->content->last_meal != 0 && temp_philo_list_head->content->last_meal - actual_time >= table->data.time_to_die)
			{
				status_printer(table, philo_list->content, DEAD);
				pthread_mutex_unlock(&temp_philo_list_head->content->data_lock);
				return ;
			}
			temp_philo_list_head = temp_philo_list_head->next;
			//pthread_mutex_unlock(&temp_philo_list_head->content->data_lock);
			if (is_each_philo_sustained(table, philo_list))
				return ;
		}
	}
}

static int manage_philosophers(t_table *table, t_philo_list *philo_list)
{
	t_philo_list	*temp_head_philo;
	t_routine_args		routine;
	int				actual_time;

	if (!table || !philo_list)
		return (-1);
	temp_head_philo = philo_list;
	while (temp_head_philo)
	{
		routine = generate_routine(table, temp_head_philo->content);
		pthread_create(&temp_head_philo->content->philo_thread, NULL, thread_routine, &routine);
		temp_head_philo = temp_head_philo->next;
	}
	while (69)
	{
		philo_checkup(actual_time, table, philo_list);
		ft_usleep(table, 10);
	}
	return (0);
}

// temporary (debug)
static void check_philo_and_fork_list(t_philo_list *philo_list)
{
	while (philo_list)
	{
		printf("PHILO ID : %zu\n", philo_list->content->philosophers_id);
		philo_list = philo_list->next;
	}
}

static int	philosophers_startup(int ac, char **av)
{
	t_table			*philo_table;
	t_philo_list	*philo_list;
	int				return_status;
	
	if (!invalid_arg(ac, av))
		return (EXIT_FAILURE);
	philo_table = init_table(ac, av);
	if (!philo_table)
		return (EXIT_FAILURE);
	philo_list = philosophers_list_init(philo_table);
	if (!philo_list)
		return (unit_table(philo_table), EXIT_FAILURE);
	//check_philo_and_fork_list(philo_list);	
	pthread_mutex_lock(&philo_table->time);
	philo_table->start_time = get_time();
	pthread_mutex_unlock(&philo_table->time);
	return_status = manage_philosophers(philo_table, philo_list);
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
