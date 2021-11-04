/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 11:50:51 by livlamin      #+#    #+#                 */
/*   Updated: 2021/11/04 14:24:26 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

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
			return (-1);
		i++;
	}
	return (0);
}
#include <unistd.h>
static int			when_thread_creation_failed(t_central *central, t_philo *philo, int i, pthread_t *thread)
{
	while (i > 0)
	{
		--i;
		if (pthread_join(thread[i], NULL) != 0)
			return (-1);
	}
	return (error_message(central, philo, 2));
}

static int	create_threads(t_central *central, t_philo *philo,
	int i, pthread_t *thread)
{

	thread = malloc(sizeof(pthread_t) * central->num_of_philo);
	while (i < central->num_of_philo)
	{
		if (i & 1) //even
		{
			if (pthread_create(&thread[i], NULL,
					routine_even_right_left, &philo[i]) != 0)
				return (when_thread_creation_failed(central, philo, i, thread));
		}
		else //odd
		{
			if (pthread_create(&thread[i], NULL,
					routine_odd_left_right, &philo[i]) != 0)
				return (when_thread_creation_failed(central, philo, i, thread));
		}
		i++;
		usleep(1000);
	}
	if (join_thread(central, thread) != 0)
	{
		free(thread);
		return (error_message(central, philo, 3));
	}
	// unlock_and_destroy(philo, central);
	// usleep(500);
	free(thread);
	return (0);
}

int	main(int argc, char **argv)
{
	t_central	*central;
	t_philo		*philo;

	philo = NULL;
	central = malloc(sizeof(t_central));
	if (!central)
		return (-1);
	if ((argc != 5 && argc != 6) || check_input(argc, argv) == -1)
		return (error_message(central, philo, 1));
	if (init_central_struct(central, argv, argc, 0) == -1)
		return (error_message(central, philo, 1));
	philo = malloc(sizeof(t_philo) * central->num_of_philo);
	if (!philo)
		return (-1);
	if (init_philo_struct(central, philo) == -1)
		return (error_message(central, philo, 1));
	if (create_threads(central, philo, 0, NULL) == -1)
		return (-1);
	unlock_and_destroy(philo, central);
	// system("leaks philo_one");
	// pthread_exit(NULL);
	return (0);
}
