# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: livlamin <livlamin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/08/16 13:26:59 by livlamin      #+#    #+#                  #
#    Updated: 2021/11/05 09:55:47 by livlamin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philosophers
SRCS = main.c \
		utils.c \
		time_and_sleep.c \
		init_structs.c \
		routine_odd_left_right.c \
		routine_even_right_left.c \
		eating.c \
		director.c \
		unlock_and_destroy.c

CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread

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