/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:03:49 by nechaara          #+#    #+#             */
/*   Updated: 2024/05/07 16:13:11 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

// MACROS
#define WRONG_EXEC "Error - Wrong exec ./philo [n1] [n2] [n3] [n4] ..[n5].."
#define WRONG_ARGS "Error - Program only takes positive numbers as arguments."
#define NOT_IN_LIMITS "Error - Arguments are not within the limits"
#define NO_EAT_LIMIT -1
// INDICES MACROS
#define NUMBER_OF_PHILOS_INDEX 1
#define TIME_TO_DIE_INDEX 2
#define TIME_TO_EAT_INDEX 3
#define TIME_TO_SLEEP_INDEX 4
#define NUMBER_OF_MEALS_INDEX 5
// LIMITS MACROS
#define NUMBER_OF_PHILOS_MIN 1
#define NUMBER_OF_PHILOS_MAX 200
#define TIME_TO_DIE_MIN 1
#define TIME_TO_DIE_MAX INT_MAX
#define TIME_TO_EAT_MIN 1
#define TIME_TO_EAT_MAX INT_MAX
#define TIME_TO_SLEEP_MIN 1
#define TIME_TO_SLEEP_MAX INT_MAX
// SIM MACROS
#define PHILO_DEAD 19
#define SIM_SUCCESS 42
#define NULL_PARAMS -1
// MESSAGES FOR OUTPUT MACROS
#define FORK_TAKEN "has taken a fork"
#define IS_SLEEPING "is sleeping"
#define IS_EATING "is eating"
#define IS_THINKING "is thinking"
#define IS_DEAD "died"