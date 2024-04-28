/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara.student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:25:28 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/28 18:47:16 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#include "macros.h"
#include "struct.h"


// OUTPUT FUNCTIONS
int				error_handler(char *message);
void			print_status(int time_stamp, size_t philo_id, char *str);
// PARSING FUNCTIONS
long			ft_strtol(const char *nptr, char **endptr, int base);
bool			invalid_arg(int ac, char **av);
void			apply_limits(t_limits *limit);
// PARSING UTILS
size_t			ft_strlen(char *str);
int				ft_is_string_number(char *str);
// INIT FUNCTIONS
t_table			*init_table(int ac, char **av);
t_philo_list	*philosophers_list_init(t_table *table, t_fork_list *fork_list);
t_fork_list		*fork_list_init(t_table *table);
void			init_id_array(t_philo_list *philo_list, t_table *philo_table);
// INIT UTILS
t_philo			*generate_philo(size_t index, t_hunger hunger_status, t_fork_list *fork_list);
t_fork			*generate_fork(size_t index);
void			init_hunger(t_table *table, t_hunger *hunger);
t_fork_list		*create_fork_list_node(t_fork *fork);
t_philo_list	*create_philo_list_node(t_philo *philo);
// UNIT FUNCTIONS
void			unit(t_fork_list *fork_list, t_philo_list *philo_list, t_table *table);
void			*unit_fork_list(t_fork_list *fork_list);
void			*unit_philo_list(t_philo_list *philo_list);
void			*unit_table(t_table *table);
void			*unit_id_array(pthread_t *id_array);
// TIME FUNCTIONS
long			get_time(void);
void			ft_usleep(int timeinms);
// THREADING ROUTINE
void			*thread_routine(void *args);
// ACTIONS 
int				philo_sleep(t_table *table, t_philo *philo);
int				philo_eat(t_philo_list *philo_list, t_philo *philo, t_table *table, int remaining_ms);
void			check_state_of_philos(int timeinms, t_philo_list *philo_list);