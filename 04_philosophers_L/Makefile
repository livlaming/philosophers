# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: livlamin <livlamin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/08/16 13:26:59 by livlamin      #+#    #+#                  #
#    Updated: 2021/10/11 13:31:10 by livlamin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_one
SRCS = main.c \
		ft_atou.c \
		init_structs.c \
		time.c \
		routine_left_right.c \
		routine_right_left.c \
		write_state.c \
		manage.c \
		hulpfunctie.c 
		# ft_itoa.c 
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
