/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_structs.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/24 17:43:57 by livlamin      #+#    #+#                 */
/*   Updated: 2021/11/29 11:57:02 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

void	init_philo_struct(t_central *central, t_philo *philo)
{
	int	ID;

	ID = 0;
	while (ID < central->num_of_philo)
	{
		philo[ID].ID = ID + 1;
		philo[ID].lfork = &central->forks[ID];
		if (ID == central->num_of_philo - 1)
			philo[ID].rfork = &central->forks[0];
		else
			philo[ID].rfork = &central->forks[ID + 1];
		philo[ID].last_eaten = central->start_time;
		philo[ID].meals_left = central->num_of_meals;
		philo[ID].central = central;
		ID++;
	}
	return ;
}

static int 	free_all(t_central *central)
{
	free(central->eat);
	free(central->write);
	free(central->status);
	free(central->full);
	return (-1);
}

static int	init_eat_write_status(t_central *central)
{
	central->eat = malloc(sizeof(pthread_mutex_t));
	central->write = malloc(sizeof(pthread_mutex_t));
	central->status = malloc(sizeof(pthread_mutex_t));
	central->full = malloc(sizeof(pthread_mutex_t));
	if (!central->eat || !central->write || !central->status || !central->full)
		return (free_all(central));
	pthread_mutex_init(central->eat, NULL);
	pthread_mutex_init(central->write, NULL);
	pthread_mutex_init(central->status, NULL);
	pthread_mutex_init(central->full, NULL);
	return (0);
}

int	init_central_struct(t_central *central, char **argv, int argc, int i)
{
	central->num_of_philo = ft_atoi(argv[1]);
	if (central->num_of_philo == 0)
		return (-2);
	central->num_of_forks = central->num_of_philo;
	central->time_to_die = ft_strtoull(argv[2]);
	central->time_to_eat = ft_strtoull(argv[3]);
	central->time_to_sleep = ft_strtoull(argv[4]);
	if (argc == 6)
		central->num_of_meals = ft_atoi(argv[5]);
	else
		central->num_of_meals = -1;
	central->forks = malloc(sizeof(pthread_mutex_t) * central->num_of_forks);
	if (!central->forks)
		return (-1);
	while (i < central->num_of_forks)
	{
		pthread_mutex_init(&central->forks[i], NULL);
		i++;
	}
	central->start_time = get_time_mseconds();
	if (init_eat_write_status(central) == -1)
		return (-1);
	central->num_of_philo_full = 0;
	central->state = ALIVE;
	return (0);
}
