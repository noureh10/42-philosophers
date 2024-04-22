/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara.student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:01:33 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/22 19:32:58 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	dining_sim(t_table *table, t_philo_list *philo_list, t_philo *philo)
{
	int	reference_time;

	reference_time = table->time_to_die;
	while (table->dead_philo)
	{
		reference_time = philo_eat(philo_list, philo, table, reference_time);
		if (reference_time <= 0)
		{
			philo->is_dead = true;
			table->dead_philo = true;
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
	while (table->dead_philo || philo->hunger.eat_counter < table->eat_limit)
	{
		philo->state_of_philo = TRANSIT_STATE;
		reference_time = philo_eat(philo_list, philo, table, reference_time);
		if (reference_time <= 0)
		{
			philo->is_dead = true;
			table->dead_philo = true;
			return ;
		}
		philo_sleep(table, philo);
		reference_time = table->time_to_die;
		philo->state_of_philo = THINK;
	}
}

void	*thread_routine(t_routine *routine)
{	
	// t_routine	*routine;
	printf("%p\n", routine->table);

	// routine = (t_routine *)arg;
	if (!routine)
		return (NULL);
	ft_usleep(routine->current_philosopher.philosophers_id * 10);
	while (!routine->table->start_dining)
		ft_usleep(200);
	// if (routine->table->eat_limit == NO_EAT_LIMIT)
	// 	dining_sim(routine->table, routine->table->head_of_philo_list, &routine->current_philosopher);
	// else
	// 	dining_sim_counter(routine->table, routine->table->head_of_philo_list, &routine->current_philosopher);
	return (NULL);
}
