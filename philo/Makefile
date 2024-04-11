# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 18:12:31 by nechaara          #+#    #+#              #
#    Updated: 2024/04/09 16:16:42 by nechaara         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = 	src/main.c src/error_handling.c src/parsing.c src/parsing_utils.c \
		src/ft_strtol.c src/init.c src/unit.c src/time.c src/init_utils.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -g -fsanitize=address #-Wall -Wextra -Werror -O3
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