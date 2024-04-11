/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:56:48 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/09 15:46:54 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
void *unit_id_array(pthread_t *id_array)
{
	size_t index;
	
	index = 0;
	if (!id_array)
		return (NULL);
	while (id_array[index])
		free(id_array[index++]);
	free(id_array);
	id_array = NULL;
	return (NULL);
}
*/

void *unit_fork_list(t_fork_list *fork_list)
{
	t_fork_list *current;
	
	if (!fork_list)
		return (NULL);
	while(fork_list)
	{
		current = fork_list;
		free(current);
		current = NULL;
		fork_list = fork_list->next;
	}
	return (NULL);
}

void *unit_philo_list(t_philo_list *philo_list)
{
	t_philo_list *current;

	if (!philo_list)
		return (NULL);
	while (philo_list)
	{
		current = philo_list;
		free(current);
		current = NULL;
		philo_list = philo_list->next;
	}
	return (NULL);
}

void *unit_table(t_table *table)
{
	if (!table)
		return (NULL);
	free(table);
	table = NULL;
	return (NULL);
}

void	unit(t_fork_list *fork_list, t_philo_list *philo_list, t_table *table)
{
	unit_fork_list(fork_list);
	unit_philo_list(philo_list);
	unit_table(table);
}
