/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara.student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:45:02 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/24 14:35:58 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_philo_list	*create_philo_list_node(t_philo *philo)
{
	t_philo_list *node;
	
	node = (t_philo_list *)malloc(sizeof(t_philo_list));
	if (!node)
		return (NULL);
	node->content = philo;
	node->next = NULL;
	return (node);
}

t_fork_list	*create_fork_list_node(t_fork *fork)
{
	t_fork_list *node;

	node = (t_fork_list *)malloc(sizeof(t_fork_list));
	if (!node)
		return (NULL);
	node->content = fork;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void init_hunger(t_table *table, t_hunger *hunger)
{
	if (!table)
		return ;
	else if (table->eat_limit == NO_EAT_LIMIT)
		return ;
	hunger->eat_counter = 0;
	hunger->is_philo_filled = false;
}

void generate_philo(t_routine routine)
{
	static t_philo 	*head_of_philo_list;
	static int		index;
	
	routine.current_philosopher.philosophers_id = routine.index;
	routine.current_philosopher.hunger = routine.hunger_status;
	routine.current_philosopher.fork = routine.fork_list->content;
	pthread_create(&routine.current_philosopher.philo, NULL, thread_routine, &routine);
}

void generate_fork(size_t index, t_fork *current_fork)
{
	if (!index)
		return ;
	pthread_mutex_init(&current_fork->fork, NULL);
	current_fork->fork_id = index;
}
