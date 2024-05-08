/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:56:48 by nechaara          #+#    #+#             */
/*   Updated: 2024/05/05 17:32:50 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void *unit_philo_list(t_philo_list *philo_list)
{
	t_philo_list *current;

	if (!philo_list)
		return (NULL);
	while (philo_list)
	{
		current = philo_list;
		pthread_exit(&current->content->philo_thread);
		pthread_mutex_destroy(&current->content->data_lock);
		pthread_mutex_destroy(&current->content->fork);
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

void	unit(t_philo_list *philo_list, t_table *table)
{
	unit_philo_list(philo_list);
	unit_table(table);
}
