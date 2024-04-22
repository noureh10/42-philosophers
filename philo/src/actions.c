/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara.student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 00:37:29 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/22 15:03:52 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// Finish function to declutter philo_eat function
static	t_philo *get_right_philo(t_philo_list *philo_list, t_philo *philo)
{
	static t_philo_list	*head_of_philo_list;
	t_philo				*right_philo;
	
	if (!head_of_philo_list)
		head_of_philo_list = philo_list;
	while (philo_list->content != philo)
		philo_list = philo_list->next;
	if (!philo_list->next)
		right_philo = head_of_philo_list->content;
	else
		right_philo = philo_list->next->content;
	return (right_philo);
}

static	int try_lock_ressource(pthread_mutex_t *mutex, int *remaining_time)
{
	long	starting_time;
	long	current_time;
	int		res;

	if (!mutex || remaining_time < 0)
		return (1);
	res = pthread_mutex_lock(mutex);
	starting_time = get_time();
	while (res != 0)
	{
		current_time = get_time();
		if (current_time - starting_time >= *remaining_time)
			return (1);
		res = pthread_mutex_lock(mutex);
	}
	*remaining_time = starting_time - current_time;
	return (0);
}

int	philo_eat(t_philo_list *philo_list, t_philo *philo, t_table *table, int remaining_ms)
{
	static t_philo_list	*head_of_philo_list;
	t_philo				*right_philo;
	int					current_time;
	int					time_at_end;
	int					time;

	if (!philo_list || !philo || !table)
		return (NULL_PARAMS);
	current_time = remaining_ms;
	right_philo = get_right_philo(philo_list, philo);
	if (try_lock_ressource(&right_philo->fork->fork, &time))
		return (philo->is_dead = true, table->dead_philo = true, PHILO_DEAD);
	if (try_lock_ressource(&philo->fork->fork, &time))
		return (philo->is_dead = true, table->dead_philo = true, PHILO_DEAD);
	philo->state_of_philo = EAT;
	ft_usleep(table->time_to_eat);
	philo->state_of_philo = TRANSIT_STATE;
	pthread_mutex_unlock(&right_philo->fork->fork);
	pthread_mutex_unlock(&philo->fork->fork);
	time_at_end = get_time();
	return (time_at_end - current_time);
}

int	philo_sleep(t_table *table, t_philo *philo)
{	
	int		current_time;
	int		time_at_end;
	
	current_time = get_time();
	philo->state_of_philo = SLEEP;
	ft_usleep(table->time_to_sleep);
	philo->state_of_philo = TRANSIT_STATE;
	time_at_end = get_time();
	return (time_at_end - current_time);
}
