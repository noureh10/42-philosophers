/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara.student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:51:52 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/02 17:52:26 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void generate_philo(size_t *index, t_philo *current_philosopher, 
	t_fork_list *fork_list, t_hunger *hunger_status)
{
	if (!index || !current_philosopher || !fork_list || hunger_status)
		return (NULL);
	current_philosopher->philosophers_id = index;
	current_philosopher->hunger_status = *hunger_status;
	current_philosopher->left_fork = fork_list->current;
	current_philosopher->right_fork = fork_list->previous;
}

static void generate_fork(size_t *index, t_fork *current_fork)
{
	if (!index || !current_fork)
		return (NULL);
	current_fork->fork_id = index;
}

t_fork_list *fork_list_init(t_table *table)
{
	t_fork_list	*fork_list;
	t_fork		current_fork;
	size_t		index;

	if (!table)
		return (NULL);
	fork_list = (t_fork_list *)malloc(sizeof(t_fork_list) * table->numbers_of_philos);
	if (!fork_list)
		return (NULL);
	index = 1;
	while (index < table->numbers_of_philos && fork_list)
	{
		generate_fork(&index, &current_fork);
		index++;
		fork_list = fork_list->next;
	}
}

t_table *init_table(int ac, char **av)
{
	t_table *table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->numbers_of_philos = ft_strtol(av[NUMBER_OF_PHILOS_INDEX], NULL, 10);
	table->time_to_die = ft_strtol(av[TIME_TO_DIE_INDEX], NULL, 10);
	table->time_to_eat = ft_strtol(av[TIME_TO_DIE_INDEX], NULL, 10);
	table->time_to_sleep = ft_strtol(av[TIME_TO_SLEEP_INDEX], NULL, 10);
	if (ac == 6)
		table->eat_limit = ft_strtol(av[EAT_LIMIT_INDEX], NULL, 10);
	else
		table->eat_limit = NO_EAT_LIMIT;
	return (table);
}

t_philo_list	*philosophers_list_init(t_table *table, t_fork_list *fork_list)
{
	t_philo_list		*philo_list;
	t_philo		current_philosopher;
	size_t		index;
	t_hunger	hunger_status;

	if (!table)
		return (NULL);
	philo_list = (t_philo_list *)malloc(sizeof(t_philo_list) * table->numbers_of_philos);
	if (!philo_list)
		return (NULL);
	index = 1;
	init_hunger(table ,&hunger_status);
	while (index < table->numbers_of_philos && philo_list)
	{
		generate_philo(&index, &current_philosopher, fork_list, &hunger_status);
		philo_list = philo_list->next;
		fork_list = fork_list->next;
		index++;
	}
	return (philo_list);
}

