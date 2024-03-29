/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 11:50:51 by livlamin      #+#    #+#                 */
/*   Updated: 2021/11/29 14:19:04 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <unistd.h>

static int	check_input(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] < '0' || argv[i][0] > '9')
			return (-1);
		i++;
	}
	return (0);
}

static int	join_thread(t_central *central, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < central->num_of_philo)
	{
		if (pthread_join(thread[i], NULL) != 0)
		{
			free(thread);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	when_thread_creation_failed(t_central *central, t_philo *philo,
	int i, pthread_t *thread)
{
	while (i > 0)
	{
		--i;
		if (pthread_join(thread[i], NULL) != 0)
			return (error_message(central, philo, 2));
	}
	free(thread);
	return (error_message(central, philo, 2));
}

static int	create_threads(t_central *central, t_philo *philo,
	int i, pthread_t *thread)
{
	thread = malloc(sizeof(pthread_t) * central->num_of_philo);
	if (!thread)
		return (error_message(central, philo, 5));
	while (i < central->num_of_philo)
	{
		if (i & 1)
		{
			if (pthread_create(&thread[i], NULL,
					routine_even_left_right, &philo[i]) != 0)
				return (when_thread_creation_failed(central, philo, i, thread));
		}
		else
		{
			if (pthread_create(&thread[i], NULL,
					routine_odd_right_left, &philo[i]) != 0)
				return (when_thread_creation_failed(central, philo, i, thread));
		}
		i++;
		usleep(1000);
	}
	if (join_thread(central, thread) != 0)
		return (error_message(central, philo, 3));
	free(thread);
	return (0);
}

int	main(int argc, char **argv)
{
	t_central	*central;
	t_philo		*philo;
	int			error;

	philo = NULL;
	central = malloc(sizeof(t_central));
	if (!central)
		return (error_message(central, philo, 6));
	if ((argc != 5 && argc != 6) || check_input(argc, argv) == -1)
		return (error_message(central, philo, 1));
	error = init_central_struct(central, argv, argc, 0);
	if (error != 0)
		return (error_message(central, philo, error));
	philo = malloc(sizeof(t_philo) * central->num_of_philo);
	if (!philo)
		return (error_message(central, philo, 4));
	init_philo_struct(central, philo);
	if (create_threads(central, philo, 0, NULL) == -1)
		return (-1);
	unlock_and_destroy(philo, central);
	return (0);
}
