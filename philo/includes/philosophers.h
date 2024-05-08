/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:25:28 by nechaara          #+#    #+#             */
/*   Updated: 2024/05/08 17:06:27 by nechaara         ###   ########.fr       */
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
int					error_handler(char *message);
void				status_printer(t_table *table, t_philo *philo, int print_code);
// PARSING FUNCTIONS
long				ft_strtol(const char *nptr, char **endptr, int base);
bool				invalid_arg(int ac, char **av);
void				apply_limits(t_limits *limit);
// PARSING UTILS
size_t				ft_strlen(char *str);
int					ft_is_string_number(char *str);
// INIT FUNCTIONS
t_table				*init_table(int ac, char **av);
t_philo_list		*philosophers_list_init(t_table *table);
void				init_id_array(t_philo_list *philo_list, t_table *philo_table);
// UNIT FUNCTIONS
void				unit(t_philo_list *philo_list, t_table *table);
void				*unit_philo_list(t_philo_list *philo_list);
void				*unit_table(t_table *table);
void				*unit_id_array(pthread_t *id_array);
// TIME FUNCTIONS
long				get_time(void);
long					get_relative_time(t_table *table);
void				ft_usleep(t_table *table , int time);
// THREADING ROUTINE
void				*thread_routine(void *args);
// ACTIONS
bool				has_philo_died(t_philo_list *philo_list);
bool				is_each_philo_sustained(t_table *table ,t_philo_list *philo_list);
void				philo_sleep(t_table *table, t_philo *philo);
void				*philo_eat(t_philo_list *philo_list, t_philo *philo, t_table *table);
void				philo_think(t_philo *philo, unsigned int timetothink);
void				philo_fork(t_table *table, t_philo *philo, t_philo_list *philo_list);
void				check_state_of_philos(int timeinms, t_philo_list *philo_list);