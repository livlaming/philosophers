# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: livlamin <livlamin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/08/16 13:26:59 by livlamin      #+#    #+#                  #
#    Updated: 2021/08/19 11:03:12 by livlamin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = main.c \
		ft_atou.c
		# ft_itoa.c \
		# ft_strdup.c
		# ft_atoi.c
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
