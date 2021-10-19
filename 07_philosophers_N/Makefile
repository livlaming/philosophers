# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: livlamin <livlamin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/08/16 13:26:59 by livlamin      #+#    #+#                  #
#    Updated: 2021/10/19 11:47:35 by livlamin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_one
SRCS = main.c \
		utils.c \
		time_and_sleep.c \
		init_structs.c \
		hulpfunc_REMOVE.c
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread
# INC = philosophers.h

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $@

san: $(SRCS)
	$(CC) $(CFLAGS) -g -fsanitize=thread $(SRCS) -o $(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) -rf $(NAME).dSYM

fclean:	clean
	$(RM) $(NAME)

re: fclean all