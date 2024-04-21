/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:51:52 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/22 00:29:25 by nechaara         ###   ########.fr       */
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
	table->start_dining = false;
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
		last_node_reference = new_node_reference;
		new_node_reference->prev = last_node_reference;
	}
	else
	{
		last_node_reference->next = new_node_reference;
		new_node_reference->prev = last_node_reference;
		last_node_reference = new_node_reference;
	}
	return (head);
}
/**
 * @brief 
 * The fork list init function returns a circular doubly-linked, representing
 * the circular nature of a table. It needs a table to have a context for the 
 * initialization of the fork_list.
 * @param table Table needed for the initialization of the fork_list
 * @param fork_list The double-pointer that we will initialize.
 */
void	fork_list_init(t_table *table, t_fork_list **fork_list)
{
	t_fork		current_working_fork;
	size_t		index;
	
	*fork_list = NULL;
	if (!table)
		return ;
	index = 0;
	while (index < table->numbers_of_philos)
	{	
		generate_fork(index, &current_working_fork);
		*fork_list = append_node_fork_list(*fork_list, &current_working_fork);
		if (!fork_list)
			return ;
		index++;
	}
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
		last_node_reference = new_node_reference;
	}
	else
	{
		last_node_reference->next = new_node_reference;
		last_node_reference = new_node_reference;
	}
	return (head);
}
/**
 * @brief 
 * The philosophers list init serve the same purpose as the fork list init.
 * It initialize a simlple linked list DS for each philosophers.
 * It need the table for context as well as the fork list since we're
 * assigning the left and right for to each content of each node in the 
 * philo_list.
 * @param table Table needed for the initialization of the philo list.
 * @param fork_list Fork list needed for the initalization of the philo list.
 * @param philo_list The double pointer that we will initialize
 */
void	philosophers_list_init(t_table *table, t_fork_list *fork_list, t_philo_list **philo_list)
{
	t_philo				current_philosopher;
	size_t				index;
	t_hunger			hunger_status;
	
	*philo_list = NULL;
	if (!table)
		return ;
	index = 0;
	init_hunger(table, &hunger_status);
	while (index < table->numbers_of_philos)
	{
		generate_philo(index, &current_philosopher, fork_list, &hunger_status);
		*philo_list = append_node_philo_list(*philo_list, &current_philosopher);
		if (!philo_list)
			return ;
		fork_list = fork_list->next;
		index++;
	}
}
