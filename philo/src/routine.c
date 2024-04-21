/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:01:33 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/22 01:26:25 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	thread_routine(t_table *table, t_philo_list *philo_list, t_philo *philo)
{
	int		last_eatten_meal;
	
	if (!table)
		return ;
	while (!table->start_dining)
		ft_usleep(150);
	
}
