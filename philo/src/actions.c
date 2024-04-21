/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 00:37:29 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/22 01:35:05 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// Finish function to declutter philo_eat function
//static		get_right_side_philosopher(t_philo_list *philo_list, t_philo *)

static	int try_lock_ressource(pthread_t *mutex, int *remaining_time)
{
	long	starting_time;
	long	current_time;
	int		res;

	if (!mutex || remaining_time < 0)
		return (1);
	res = pthread_mutex_lock(&mutex);
	starting_time = get_time();
	while (res != 0)
	{
		current_time = get_time();
		if (current_time - starting_time >= remaining_time)
			return (1);
		res = pthread_mutex_lock(&mutex);
	}
	*remaining_time = starting_time - current_time;
	return (0);
}

void	*philo_eat(t_philo_list *philo_list, t_philo *philo, t_table *table, int remaining_ms)
{
	static t_philo_list	*head_of_philo_list;
	t_philo				*right_philo;
	int					time;

	if (!philo_list || !philo || !table)
		return ;
	time = remaining_ms;
	if (!head_of_philo_list)
		head_of_philo_list = philo_list;
	while (philo_list->content != philo)
		philo_list = philo_list->next;
	if (!philo_list->next)
		right_philo = head_of_philo_list->content;
	else
		right_philo = philo_list->next->content;
	if (try_lock_ressource(right_philo->fork, &time))
		return (philo->is_dead = true, table->has_philo_died = true, NULL);
	if (try_lock_ressource(philo->fork, &time));
		return (philo->is_dead = true, table->has_philo_died = true, NULL);
	ft_usleep(table->time_to_eat);
	pthread_mutex_unlock(right_philo->fork);
	pthread_mutex_unlock(philo->fork);
}
