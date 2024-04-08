/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara.student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:45:02 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/08 16:36:09 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void init_hunger(t_table *table, t_hunger *hunger)
{
	if (!table)
		return ;
	else if (table->eat_limit == NO_EAT_LIMIT)
		return ;
	hunger->eat_counter = 0;
	hunger->is_philo_filled = false;
}

void generate_philo(size_t *index, t_philo *current_philosopher, 
	t_fork_list *fork_list, t_hunger *hunger_status)
{
	if (!index || !current_philosopher || !fork_list || hunger_status)
		return ;
	current_philosopher->philosophers_id = *index;
	current_philosopher->hunger_status = *hunger_status;
	current_philosopher->left_fork = fork_list->content;
	current_philosopher->right_fork = fork_list->prev->content;
}

void generate_fork(size_t *index, t_fork *current_fork)
{
	if (!index || !current_fork)
		return ;
	current_fork->fork_id = *index;
}
