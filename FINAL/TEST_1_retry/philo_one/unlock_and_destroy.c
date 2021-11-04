/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unlock_and_destroy.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 11:19:03 by livlamin      #+#    #+#                 */
/*   Updated: 2021/11/04 14:22:58 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

void	destroy_forks(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->central->num_of_forks)
	{
		// pthread_mutex_unlock(&philo->central->forks[i]);
		pthread_mutex_destroy(&philo->central->forks[i]);
		i++;
	}
}

void	destroy_mutex(t_philo *philo)
{
	pthread_mutex_destroy(philo->central->eat);
	pthread_mutex_destroy(philo->central->write);
	pthread_mutex_destroy(philo->central->status);
	pthread_mutex_destroy(philo->central->full);
	free(philo->central->eat);
	free(philo->central->write);
	free(philo->central->status);
	free(philo->central->forks);
}

void	unlock_and_destroy(t_philo *philo, t_central *central)
{
	destroy_forks(philo);
	destroy_mutex(philo);
	free(philo);
	free(central);
}
