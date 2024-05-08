/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:51:52 by nechaara          #+#    #+#             */
/*   Updated: 2024/05/08 14:49:32 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_table *init_table(int ac, char **av)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->philo_died = false;
	table->start_dining = false;
	table->start_time = 0;
	table->data.number_of_philos = ft_strtol(av[NUMBER_OF_PHILOS_INDEX], NULL, 10);
	table->data.time_to_die = ft_strtol(av[TIME_TO_DIE_INDEX], NULL, 10);
	table->data.time_to_eat = ft_strtol(av[TIME_TO_EAT_INDEX], NULL, 10);
	table->data.time_to_sleep = ft_strtol(av[TIME_TO_SLEEP_INDEX], NULL, 10);
	if (ac == 6)
		table->data.number_of_required_meals = ft_strtol(av[NUMBER_OF_MEALS_INDEX], NULL, 10);
	else
		table->data.number_of_required_meals = NO_EAT_LIMIT;
	pthread_mutex_init(&table->table, NULL);
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->time, NULL);
	return (table);
}

static t_philo_list	*create_philo_list_node(t_philo *philo)
{
	t_philo_list *node;
	
	node = (t_philo_list *)malloc(sizeof(t_philo_list));
	if (!node)
		return (NULL);
	node->content = philo;
	node->next = NULL;
	return (node);
}

static t_philo	*generate_philo(size_t index)
{	
	t_philo	*current_philosopher;
	
	current_philosopher = (t_philo *)malloc(sizeof(t_philo));
	if (!current_philosopher)
		return (NULL);
	current_philosopher->is_dead = false;
	current_philosopher->philosophers_id = index;
	current_philosopher->last_meal = 0;
	current_philosopher->number_of_meals = 0;
	pthread_mutex_init(&current_philosopher->fork, NULL);
	pthread_mutex_init(&current_philosopher->data_lock, NULL);
	return (current_philosopher);
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
 * The philosophers list init serve the same purpose as the fork list init.
 * It initialize a simlple linked list DS for each philosophers.
 * It need the table for context as well as the fork list since we're
 * assigning the left and right for to each content of each node in the 
 * philo_list.
 * @param table Table needed for the initialization of the philo list.
 * @param fork_list Fork list needed for the initalization of the philo list.
 * @param philo_list The double pointer that we will initialize.
 */
t_philo_list	*philosophers_list_init(t_table *table)
{	
	t_philo_list	*philo_list;
	t_philo			*current_philosopher;
	size_t			index;
	
	philo_list = NULL;
	index = 0;
	while (index < table->data.number_of_philos)
	{
		current_philosopher = generate_philo(index);
		if (!current_philosopher)
			return (NULL);
		philo_list = append_node_philo_list(philo_list, current_philosopher);
		if (!philo_list)
			return (free(current_philosopher), current_philosopher = NULL, NULL);
		if (index == 0)
			table->philo_list_head = philo_list;
		index++;
	}
	return (philo_list);
}
