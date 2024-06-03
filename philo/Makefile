# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nechaara <nechaara.student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 18:12:31 by nechaara          #+#    #+#              #
#    Updated: 2024/06/03 13:10:33 by nechaara         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = 	init_and_unit/init_and_unit.c parsing/parsing_strtol.c parsing/parsing_utils.c \
		parsing/parsing.c thread_routine/state.c thread_routine/routine.c thread_routine/utils.c \
		time/time.c main.c 

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 #-fsanitize=thread
RM = rm -f

GREEN=\033[0;32m
NC=\033[0m

all : $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) has been created successfully.$(NC)"
	@echo "Use it this way : ./philo [NUMBER_OF_PHILOS] [TIME_TO_DIE] [TIME_TO_EAT] [TIME_TO_SLEEP] [-OPTIONAL- EAT_LIMIT]"

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SILENT: