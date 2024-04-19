/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara.student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:03:57 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/19 19:10:01 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

typedef enum e_state
{
	EAT,
	SLEEP,
	THINK
}	t_state;

typedef struct s_bound
{
	long	number_of_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
}	t_bound;

typedef struct s_limits
{
	t_bound arg_max;
	t_bound arg_min;
}	t_limits;

typedef struct s_fork
{
	pthread_t	fork;
	int			fork_id;
}	t_fork;

typedef struct s_fork_list
{
	struct	s_fork		*content;
	bool				first_element;
	struct	s_fork_list *prev;
	struct	s_fork_list	*next;
}	t_fork_list;

typedef struct s_hunger
{
	size_t	eat_counter;
	bool	is_philo_filled;
}	t_hunger;

typedef struct s_philo
{
	int			philosophers_id;
	pthread_t	philo;
	t_state		state_of_philo;
	t_hunger	hunger_status;
	t_fork		*left_fork;
	t_fork		*right_fork;
}	t_philo;

typedef struct s_philo_list
{
	struct s_philo		*content;
	struct s_philo_list	*next;
}	t_philo_list;

typedef struct s_table
{
	long	numbers_of_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	eat_limit;
	bool	start_dining;
	bool	has_philo_died;
}	t_table;

typedef struct s_time
{
	long	starting_time;
	long	ending_time;
}	t_time;