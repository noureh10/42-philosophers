/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara.student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:51:52 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/28 18:42:07 by nechaara         ###   ########.fr       */
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
	table->head_of_philo_list = NULL;
	table->head_of_fork_list = NULL;
	table->finished_sim = false;
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
 * The fork list init function returns a doubly-linked, representing a table. 
 * It needs a table to have a context for the initialization of the fork_list.
 * @param table Table needed for the initialization of the fork_list
 * @param fork_list The double-pointer that we will initialize.
 */
t_fork_list		*fork_list_init(t_table *table)
{
	size_t		index;
	t_fork		*current_fork;
	t_fork_list	*fork_list;

	fork_list = NULL;
	index = 0;
	while (index < table->numbers_of_philos)
	{	
		current_fork = generate_fork(index);
		fork_list = append_node_fork_list(fork_list, current_fork);
		if (!fork_list)
			return (NULL);
		index++;
	}
	return (fork_list);
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
 * @param philo_list The double pointer that we will initialize.
 */
t_philo_list	*philosophers_list_init(t_table *table, t_fork_list *fork_list)
{	
	t_philo_list	*philo_list;
	t_philo			*current_philosopher;
	size_t			index;
	t_hunger		hunger_status;
	
	philo_list = NULL;
	index = 0;
	init_hunger(table, &hunger_status);
	while (index < table->numbers_of_philos)
	{
		current_philosopher = generate_philo(index, hunger_status, fork_list);
		if (!current_philosopher)
			return (NULL);
		philo_list = append_node_philo_list(philo_list, current_philosopher);
		if (!philo_list)
			return (free(current_philosopher), current_philosopher = NULL, NULL);
		if (index == 0)
			table->head_of_philo_list = philo_list;
		fork_list = fork_list->next;
		index++;
	}
	return (philo_list);
}
