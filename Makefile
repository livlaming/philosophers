# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: livlamin <livlamin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/08/16 13:26:59 by livlamin      #+#    #+#                  #
#    Updated: 2021/08/17 15:06:44 by livlamin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = main.c \
		ft_atou.c
		# ft_atoi.c
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread
# INC = philosophers.h

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $@

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re: fclean all
