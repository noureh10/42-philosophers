/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 00:37:29 by nechaara          #+#    #+#             */
/*   Updated: 2024/05/08 17:07:42 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	status_printer(t_table *table, t_philo *philo, int print_code)
{
	int	index;

	if (!table || !philo)
		return ;
	index = (int) philo->philosophers_id + 1;
	pthread_mutex_lock(&table->print);
	if (!has_philo_died(table->philo_list_head))
	{
		if (print_code == FORK)
			printf("%ld %d %s\n", get_relative_time(table), index, FORK_TAKEN);
		else if (print_code == EAT)
			printf("%ld %d %s\n", get_relative_time(table), index, IS_EATING);
		else if (print_code == SLEEP)
			printf("%ld %d %s\n", get_relative_time(table), index, IS_SLEEPING);
		else if (print_code == THINK)
			printf("%ld %d %s\n", get_relative_time(table), index, IS_THINKING);
		else if (print_code == DEAD)
		{
			printf("%ld %d %s\n", get_relative_time(table), index, IS_DEAD);
			pthread_mutex_lock(&philo->data_lock);
			philo->is_dead = true;
			pthread_mutex_unlock(&philo->data_lock);
		}
	}
	pthread_mutex_unlock(&table->print);
}

static	t_philo *get_right_philo(t_table *table, t_philo_list *philo_list, t_philo *philo)
{
	static t_philo_list	*head_of_philo_list;
	t_philo				*right_philo;
	
	pthread_mutex_lock(&table->time);
	if (!head_of_philo_list)
		head_of_philo_list = philo_list;
	while (philo_list->content != philo)
		philo_list = philo_list->next;
	if (!philo_list->next)
		right_philo = head_of_philo_list->content;
	else
		right_philo = philo_list->next->content;
	pthread_mutex_unlock(&table->time);
	return (right_philo);
}

void	*philo_eat(t_philo_list *philo_list, t_philo *philo, t_table *table)
{
	t_philo				*right_philo;

	if (!philo_list || !philo || !table)
		return (NULL);
	right_philo = get_right_philo(table, philo_list, philo);
	status_printer(table, philo, EAT);
	pthread_mutex_lock(&philo->data_lock);
	philo->last_meal = get_relative_time(table);
	philo->number_of_meals+=1;
	pthread_mutex_unlock(&philo->data_lock);
	ft_usleep(table, table->data.time_to_eat);
	pthread_mutex_unlock(&right_philo->fork);
	pthread_mutex_unlock(&philo->fork);
}

void	philo_sleep(t_table *table, t_philo *philo)
{	
	if (!table || !philo)
		return ;
	status_printer(table, philo, SLEEP);
	ft_usleep(table, table->data.time_to_sleep);
}

void	philo_fork(t_table *table, t_philo *philo, t_philo_list *philo_list)
{
	t_philo		*right_philo;

	if (!table || !philo || !philo_list)
		return ;
	right_philo = get_right_philo(table, philo_list, philo);
	pthread_mutex_lock(&philo->fork);
	status_printer(table, philo, FORK);
	pthread_mutex_lock(&right_philo->fork);
	status_printer(table, philo, FORK);
}