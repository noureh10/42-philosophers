/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara.student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:52:03 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/28 22:25:45 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"


void	test(int a, int b)
{
	
}

long	get_time(void)
{
	long			time;
	struct	timeval	time_value;

	gettimeofday(&time_value, NULL);
	time = (time_value.tv_sec * 1000 + time_value.tv_usec / 1000);
	return (time);
}

void	ft_usleep(int timeinms)
{
	long	time;

	time = get_time();
	while (get_time() - time < timeinms)
		usleep(500);
}
