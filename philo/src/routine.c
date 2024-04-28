/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara.student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:01:33 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/28 18:30:13 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	dining_sim(t_table *table, t_philo_list *philo_list, t_philo *philo)
{
	int	reference_time;

	reference_time = table->time_to_die;
	while (!table->finished_sim)
	{
		reference_time = philo_eat(philo_list, philo, table, reference_time);
		if (reference_time <= 0)
		{
			philo->is_dead = true;
			table->finished_sim = true;
			return ;
		}
		philo_sleep(table, philo);
		reference_time = table->time_to_die;
	}
}

static void dining_sim_counter(t_table *table, t_philo_list *philo_list, t_philo *philo)
{
	int reference_time;

	reference_time = table->time_to_die;
	while (!table->finished_sim || philo->hunger.eat_counter < table->eat_limit)
	{
		philo->state_of_philo = TRANSIT_STATE;
		reference_time = philo_eat(philo_list, philo, table, reference_time);
		if (reference_time <= 0)
		{
			philo->is_dead = true;
			table->finished_sim = true;
			return ;
		}
		philo_sleep(table, philo);
		reference_time = table->time_to_die;
		philo->state_of_philo = THINK;
	}
}

void	*thread_routine(void *args)
{	
	t_routine	*routine;
	routine = (t_routine *)args;
	if (!routine || !routine->current_philosopher || !routine->table)
		return (NULL);
	ft_usleep((routine->current_philosopher->philosophers_id + 1) * 10);
	while (!routine->table->start_dining)
		ft_usleep(500);
	if (routine->table->eat_limit == NO_EAT_LIMIT)
		dining_sim(routine->table, routine->table->head_of_philo_list, routine->current_philosopher);
	else
		dining_sim_counter(routine->table, routine->table->head_of_philo_list, routine->current_philosopher);
	return (NULL);
}
