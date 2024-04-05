/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:25:28 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/05 23:10:33 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

// MACROS
#define WRONG_EXEC "Error - Wrong exec ./philo [n1] [n2] [n3] [n4] ..[n5].."
#define WRONG_ARGS "Error - Program only takes positive numbers as arguments."
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

typedef struct s_fork_list
{
	struct	s_fork *current;
	struct	s_fork *previous;
	struct	s_fort *next;
}	t_fork_list;

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
	t_fork		*left_fork;
	t_fork		*right_fork;
}	t_philo;

typedef struct s_philo_list
{
	struct s_philo	*current_philo;
	struct s_philo	*next;
}	t_philo_list;

typedef struct s_table
{
	long	numbers_of_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	eat_limit;
}	t_table;

// PARSING FUNCTIONS
int				error_handler(char *message);
long			ft_strtol(const char *nptr, char **endptr, int base);
bool			invalid_arg(int ac, char **av);
// INIT FUNCTIONS
t_table			*init_table(int ac, char **av);
t_philo_list	*philosophers_list_init(t_table *table, t_fork_list *fork_list);
t_fork_list		*fork_list_init(t_table *table);
// UNIT FUNCTIONS
void			unit(t_fork_list *fork_list, t_philo_list *philo_list, t_table *table);
void			*unit_fork_list(t_fork_list *fork_list);
void			*unit_philo_list(t_philo_list *philo_list);
void			*unit_table(t_table *table);
