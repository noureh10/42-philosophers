/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:25:28 by nechaara          #+#    #+#             */
/*   Updated: 2024/03/26 18:00:36 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>

// MACROS
#define WRONG_EXEC "Error - Wrong exec"
#define NO_EAT_LIMIT -1
// INDICES MACROS
#define NUMBER_OF_PHILOS_INDEX 0
#define TIME_TO_DIE_INDEX 1
#define TIME_TO_EAT_INDEX 2
#define TIME_TO_SLEEP_INDEX 3
#define EAT_LIMIT_INDEX 4
// ENUMS

typedef enum e_state
{
	EAT,
	SLEEP,
	THINK
}	t_state;
// STRUCTURES
typedef pthread_t	t_mutex;

typedef struct s_fork
{
	t_mutex	fork;
	int		fork_id;
}	t_fork;

typedef struct s_hunger
{
	size_t	eat_counter;
	bool	is_philo_filled;
}	t_hunger;

typedef struct s_philo
{
	int			philosophers_id;
	t_state		state_of_philo;
	t_hunger	hunger_status;
	t_fork		left_fork;
	t_fork		right_fork;
}	t_philo;

typedef struct s_list
{
	struct s_philo	current_philo;
	struct s_philo	*next;
}	t_list;

typedef struct s_table
{
	size_t	numbers_of_philos;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		eat_limit;
}	t_table;

// FUNCTIONS
int		error_handler(char *message);
long	ft_strtol(const char *nptr, char **endptr, int base);
bool	invalid_arg(int ac, char **av);