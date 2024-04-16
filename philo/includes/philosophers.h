/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara.student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:25:28 by nechaara          #+#    #+#             */
/*   Updated: 2024/04/16 17:08:22 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#include "macros.h"
#include "struct.h"

// PARSING FUNCTIONS
int				error_handler(char *message);
long			ft_strtol(const char *nptr, char **endptr, int base);
bool			invalid_arg(int ac, char **av);
void			apply_limits(t_limits *limit);
// PARSING UTILS
size_t			ft_strlen(char *str);
int				ft_is_string_number(char *str);
// INIT FUNCTIONS
t_table			*init_table(int ac, char **av);
void			*philosophers_list_init(t_table *table, t_fork_list *fork_list, t_philo_list **philo_list);
t_fork_list		*fork_list_init(t_table *table, t_fork_list **fork_list);
pthread_t		*init_id_array(t_philo_list *philo_list, t_table *philo_table);
// INIT UTILS
void			generate_philo(size_t *index, t_philo *current_philosopher, 
	t_fork_list *fork_list, t_hunger *hunger_status);
void			generate_fork(size_t *index, t_fork *current_fork);
void			init_hunger(t_table *table, t_hunger *hunger);
t_fork_list		*create_fork_list_node(t_fork *fork);
t_philo_list	*create_philo_list_node(t_philo *philo);
// UNIT FUNCTIONS
void			unit(t_fork_list *fork_list, t_philo_list *philo_list, t_table *table);
void			*unit_fork_list(t_fork_list *fork_list);
void			*unit_philo_list(t_philo_list *philo_list);
void			*unit_table(t_table *table);
void			*unit_id_array(pthread_t *id_array);
// THREADING ROUTINE
void			thread_routine(void);
