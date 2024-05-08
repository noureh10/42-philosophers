/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:01:33 by nechaara          #+#    #+#             */
/*   Updated: 2024/05/08 17:09:17 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool		has_philo_died(t_philo_list *philo_list)
{
	t_philo_list *temp;

	if (!philo_list)
		return (false);
	temp = philo_list;
	while (temp)
	{
		pthread_mutex_lock(&temp->content->data_lock);
		if (temp->content->is_dead)
		{
			pthread_mutex_unlock(&temp->content->data_lock);
			return (true);
		}
		pthread_mutex_unlock(&temp->content->data_lock);
		temp = temp->next;
	}
	return (true);
}

bool		is_each_philo_sustained(t_table *table ,t_philo_list *philo_list)
{
	if (!table || !philo_list)
		return (false);
	else if (table->data.number_of_required_meals == NO_EAT_LIMIT)
		return (false);
	while (philo_list)
	{
		if (philo_list->content->number_of_meals != table->data.number_of_required_meals)
			return (false);
		philo_list = philo_list->next;
	}
	pthread_mutex_lock(&table->table);
	table->philo_died = false;
	pthread_mutex_lock(&table->table);
	return (true);
}

static int	dining_sim(t_table *table, t_philo_list *philo_list, t_philo *philo)
{
	while (!has_philo_died(philo_list))
	{
		if (table->data.number_of_philos > 1)
		{
			philo_fork(table, philo, philo_list);
			philo_eat(philo_list, philo, table);
			if (table->data.number_of_required_meals == philo->number_of_meals)
				return (SIM_SUCCESS);
		}
		philo_sleep(table, philo);
		status_printer(table, philo, THINK);
	}
	return (PHILO_DEAD);
}
void	*thread_routine(void *args)
{
	t_routine_args *routine;
	
	routine = (t_routine_args *) args;
	if (!routine->current_philosopher || !routine->table)
		return (NULL);
	if (routine->table->data.number_of_philos % 2 == 0)
		ft_usleep(routine->table, routine->table->data.time_to_eat / 10);
	dining_sim(routine->table, routine->table->philo_list_head, routine->current_philosopher);
	return (NULL);
}

