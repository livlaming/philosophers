# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: livlamin <livlamin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/03 11:51:33 by livlamin      #+#    #+#                  #
#    Updated: 2021/11/03 11:51:49 by livlamin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_one
SRCS = main.c
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread
#-g
# INC = philosophers.h

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $@

san: $(SRCS)
	$(CC) $(CFLAGS) -g -fsanitize=thread $(SRCS) -o $(NAME)

debug: $(SRCS)
	$(CC) $(CFLAGS) -g $(SRCS) -o $(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) -rf $(NAME).dSYM

fclean:	clean
	$(RM) $(NAME)

re: fclean all