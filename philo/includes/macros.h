/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:03:49 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/09 16:05:26 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

// MACROS
#define WRONG_EXEC "Error - Wrong exec ./philo [n1] [n2] [n3] [n4] ..[n5].."
#define WRONG_ARGS "Error - Program only takes positive numbers as arguments."
#define ID_ARRAY_NO_INIT "Error - Couldn't init the ID array, needed for threading."
#define NO_EAT_LIMIT -1
// INDICES MACROS
#define NUMBER_OF_PHILOS_INDEX 1
#define TIME_TO_DIE_INDEX 2
#define TIME_TO_EAT_INDEX 3
#define TIME_TO_SLEEP_INDEX 4
#define EAT_LIMIT_INDEX 5
// LIMITS MACROS
#define NUMBER_OF_PHILOS_MIN 1
#define NUMBER_OF_PHILOS_MAX 200
#define TIME_TO_DIE_MIN 1
#define TIME_TO_DIE_MAX INT_MAX
#define TIME_TO_EAT_MIN 60
#define TIME_TO_EAT_MAX INT_MAX
#define TIME_TO_SLEEP_MIN 1
#define TIME_TO_SLEEP_MAX INT_MAX