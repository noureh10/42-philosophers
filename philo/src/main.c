/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:24:50 by nechaara          #+#    #+#             */
/*   Updated: 2024/03/25 18:19:36 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int main(int ac, char **av)
{
	if (!((ac == 5) ^ (ac == 6)))
		return (error_handler(WRONG_EXEC));
	else
		printf("place holder");
}