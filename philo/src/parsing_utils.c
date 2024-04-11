/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:36:14 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/11 15:14:12 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void apply_bounds(t_bound *min, t_bound *max)
{
	min->number_of_philos = NUMBER_OF_PHILOS_MIN;
	min->time_to_die = TIME_TO_DIE_MIN;
	min->time_to_eat = TIME_TO_EAT_MIN;
	min->time_to_sleep = TIME_TO_SLEEP_MIN;
	max->number_of_philos = NUMBER_OF_PHILOS_MAX;
	max->time_to_die = TIME_TO_DIE_MAX;
	max->time_to_eat = TIME_TO_EAT_MAX;
	max->time_to_sleep = TIME_TO_SLEEP_MAX;
}

void apply_limits(t_limits *limit)
{
	apply_bounds(&limit->arg_min, &limit->arg_max);
}