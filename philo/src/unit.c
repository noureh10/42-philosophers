/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara.student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:56:48 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/03 16:34:54 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void *unit_fork_list(t_fork_list *fork_list)
{
	t_fork_list *current;
	
	if (!fork_list)
		return ;
	while(fork_list)
	{
		current = fork_list;
		free(current);
		current = NULL;
		fork_list = fork_list->next;
	}
}

void *unit_philo_list(t_philo_list *philo_list)
{
	t_philo_list *current;

	if (!philo_list)
		return ;
	while (philo_list)
	{
		current = philo_list;
		free(current);
		current = NULL;
		philo_list = philo_list->next;
	}
}

void *unit_table(t_table *table)
{
	if (!table)
		return (NULL);
	free(table);
	table = NULL;
}

void	*unit(t_fork_list *fork_list, t_philo_list *philo_list, t_table *table)
{
	unit_fork_list(fork_list);
	unit_philo_list(philo_list);
	unit_table(table);
}
