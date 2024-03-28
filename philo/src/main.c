/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:24:50 by nechaara          #+#    #+#             */
/*   Updated: 2024/03/28 14:48:05 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	manage_philosophers(int ac, char **av)
{
	if (!invalid_arg(ac, av))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	if (!((ac == 5) ^ (ac == 6)))
		return (error_handler(WRONG_EXEC));
	else
		return (manage_philosophers(ac, av));
}
