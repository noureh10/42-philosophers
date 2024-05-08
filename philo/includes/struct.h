/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:03:57 by nechaara          #+#    #+#             */
/*   Updated: 2024/05/08 15:40:36 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

typedef enum e_state
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD
}	t_state;

typedef struct s_data
{
	size_t	number_of_philos;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	number_of_required_meals;
}	t_data;

typedef struct s_limits
{
	t_data arg_max;
	t_data arg_min;
}	t_limits;

typedef struct s_philo
{
	size_t			philosophers_id;
	pthread_t		philo_thread;
	pthread_mutex_t	data_lock;
	unsigned int	last_meal;
	size_t			number_of_meals;
	bool			is_dead;
	pthread_mutex_t	fork;
}	t_philo;

typedef struct s_philo_list
{
	struct s_philo		*content;
	struct s_philo_list	*next;
	struct s_philo_list *prev;
}	t_philo_list;

typedef struct s_table
{
	long			start_time;
	t_data			data;
	t_philo_list	*philo_list_head;
	bool			philo_died;
	bool			start_dining;
	pthread_mutex_t	table;
	pthread_mutex_t	print;
	pthread_mutex_t	time;
	pthread_mutex_t eat;
}	t_table;

typedef struct s_routine_args
{
	t_table 		*table;
	t_philo			*current_philosopher;
}	t_routine_args;