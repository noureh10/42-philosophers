/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:24:50 by nechaara          #+#    #+#             */
/*   Updated: 2024/03/26 18:21:26 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	manage_philosophers(int ac, char **av)
{
	if (!invalid_arg(ac, av))
	{
		printf("byebye");
		return (1);
	}
}

int main(int ac, char **av)
{
	if (!((ac == 5) ^ (ac == 6)))
		return (error_handler(WRONG_EXEC));
	else
		return (manage_philosophers(ac, av));
}