/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:01:58 by nechaara          #+#    #+#             */
/*   Updated: 2024/05/31 09:42:21 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>

// ERRORS MACROS
#define WRONG_EXEC "Error - Wrong exec ./philo [n1] [n2] [n3] [n4] ..[n5].."
#define WRONG_ARGS "Error - Program only takes positive integers as arguments."
#define NOT_IN_LIMITS "Error - Arguments are not within the limits."
#define WR_NUM_OF_PHIL  "Error - Wrong range for number of philos [1 - 200]"
#define WR_TIME_TO_DIE  "Error - Wrong range for time to die [60 - INT_MAX]"
#define WR_TIME_TO_EAT  "Error - Wrong range for time to eat [60 - INT_MAX]"
#define WR_TIME_TO_SLEEP  "Error - Wrong range for time to sleep [60 - INT_MAX]"
#define WR_NUM_OF_MEALS  "Error - Wrong range for number of meals [0 - INT_MAX]"

// MESSAGES MACROS
#define FORK_M "has taken a fork"
#define SLEEP_M "is sleeping"
#define EAT_M "is eating"
#define THINK_M "is thinking"
#define DEAD_M "died"

// LIMITS MACROS
#define NUMBER_OF_PHILOS_MIN 1
#define NUMBER_OF_PHILOS_MAX 200
#define TIME_TO_DIE_MIN 60
#define TIME_TO_DIE_MAX INT_MAX
#define TIME_TO_EAT_MIN 60
#define TIME_TO_EAT_MAX INT_MAX
#define TIME_TO_SLEEP_MIN 60
#define TIME_TO_SLEEP_MAX INT_MAX
#define NUMBER_OF_REQUIRED_MEALS_MIN 0
#define NUMBER_OF_REQUIRED_MEALS_MAX INT_MAX

//ERROR MACROS
#define NULL_PARAMS -42

typedef pthread_mutex_t	t_mutex;

typedef enum e_state
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD
}	t_state;

typedef struct s_philo
{
	size_t			philosophers_id;
	pthread_t		philo_thread;
	t_mutex			fork;
	t_mutex			death_lock;
	size_t			num_of_meals;
	int				last_meal;
	bool			is_dead;
}	t_philo;

typedef struct s_data
{
	size_t	number_of_philos;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		num_of_meals;
}	t_data;

typedef struct s_limits
{
	t_data	arg_max;
	t_data	arg_min;
}	t_limits;

typedef struct s_table
{
	size_t		start_time;
	t_data		data;
	t_philo		*philo;
	bool		is_sim_finished;
	t_mutex		table;
	t_mutex		meal_time;
	t_mutex		death_mtx;
	t_mutex		print;
	t_mutex		time;
}	t_table;

typedef struct s_routine_args
{
	t_table		*table;
	size_t		index;	
}	t_routine_args;

typedef t_routine_args	t_rargs;

// PARSING FOR STRONG INPUT
bool	invalid_arg(int ac, char **av);
long	ft_strtol(const char *nptr, char **endptr, int base);
void	set_argv_value_to_struct(t_data *values, int ac, char **av);
int		ft_is_string_number(char *str);
// INIT
bool	init_table(t_table *table);
bool	parsing_data(t_table *table, int ac, char **av);
t_rargs	*set_routine_args(t_table *table);
// ACTIONS
void	philo_fork(t_table *table, size_t current_philo, size_t left_philo);
void	philo_sleep(t_table *table, size_t current_philo);
void	philo_eat(t_table *table, size_t current_philo, size_t left_philo);
// OUTPUT
void	status_printer(t_table *table, size_t philo_index, int print_code);
int		error_handler(char *message);
// TIME
int		real_time(void);
void	ft_usleep(t_table *table, int time);
int		get_time(t_table *data);
// THREAD
void	*manager_philosophers(void *args);
void	*routine(void *args);
void	unit_table(t_table *table);
bool	check_hunger(t_table *table);
//UTILS
size_t	get_left_philosopher(t_table *table, size_t current_philo);