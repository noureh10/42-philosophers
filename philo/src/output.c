/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara.student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:41:10 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/28 18:44:25 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	error_handler(char *message)
{
	printf("%s\n", message);
	return (EXIT_FAILURE);
}

void print_status(int time_stamp, size_t philo_id, char *str)
{
	printf("%d philo %zu %s\n", time_stamp, philo_id, str);
}