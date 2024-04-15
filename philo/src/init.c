/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara.student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:51:52 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/15 14:53:56 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_table *init_table(int ac, char **av)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->numbers_of_philos = ft_strtol(av[NUMBER_OF_PHILOS_INDEX], NULL, 10);
	table->time_to_die = ft_strtol(av[TIME_TO_DIE_INDEX], NULL, 10);
	table->time_to_eat = ft_strtol(av[TIME_TO_EAT_INDEX], NULL, 10);
	table->time_to_sleep = ft_strtol(av[TIME_TO_SLEEP_INDEX], NULL, 10);
	if (ac == 6)
		table->eat_limit = ft_strtol(av[EAT_LIMIT_INDEX], NULL, 10);
	else
		table->eat_limit = NO_EAT_LIMIT;
	return (table);
}

t_fork_list	*append_node_fork_list(t_fork_list *head, t_fork *fork)
{
	static	t_fork_list		*last_node_reference;
	t_fork_list				*new_node_reference;
	t_fork_list				*current_node_reference;

	new_node_reference = create_fork_list_node(fork);
	if (!new_node_reference)
		return (NULL);
	if (!last_node_reference)
	{
		if (!head)
			return (new_node_reference);
		current_node_reference = head;
		while (current_node_reference->next)
			current_node_reference = current_node_reference->next;
		current_node_reference->next = new_node_reference;
	}
	else
		last_node_reference->next = new_node_reference;
	new_node_reference->prev = last_node_reference;
	last_node_reference = new_node_reference;
	return (head);
}

t_philo_list *append_node_philo_list(t_philo_list *head, t_philo *philo)
{
	static	t_philo_list	*last_node_reference;
	t_philo_list			*new_node_reference;
	t_philo_list			*current_node_reference;
	
	new_node_reference = create_philo_list_node(philo);
	if (!new_node_reference)
		return (NULL);
	if (!last_node_reference)
	{
		if (!head)
			return (new_node_reference);
		current_node_reference = head;
		while (current_node_reference->next)
			current_node_reference = current_node_reference->next;
		current_node_reference->next = new_node_reference;
	}
	else
		last_node_reference->next = new_node_reference;
	last_node_reference = new_node_reference;
	return (head);
}

t_fork_list *fork_list_init(t_table *table)
{
	t_fork_list	**fork_list;
	t_fork		current_working_fork;
	size_t		index;

	if (!table)
		return (NULL);
	index = 0;
	fork_list = NULL;
	while (index < table->numbers_of_philos)
	{	
		generate_fork(&index, &current_working_fork);
		*fork_list = append_node_fork_list(*fork_list, &current_working_fork);
		index++;
	}
	return (*fork_list);
}

t_philo_list	*philosophers_list_init(t_table *table, t_fork_list *fork_list)
{
	t_philo_list		**philo_list;
	t_philo				current_philosopher;
	size_t				index;
	t_hunger			hunger_status;

	if (!table)
		return (NULL);
	index = 0;
	philo_list = NULL;
	init_hunger(table, &hunger_status);
	while (index < table->numbers_of_philos)
	{
		generate_philo(&index, &current_philosopher, fork_list, &hunger_status);
		*philo_list = append_node_philo_list(*philo_list, &current_philosopher);
		index++;
	}
	return (*philo_list);
}
