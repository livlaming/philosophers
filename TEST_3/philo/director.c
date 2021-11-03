/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   director.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 13:14:35 by livlamin      #+#    #+#                 */
/*   Updated: 2021/11/02 14:02:35 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	*philosophers_full(t_philo *philo)
{	
	pthread_mutex_lock(philo->central->status);
	philo->central->state =	DEAD;
	pthread_mutex_unlock(philo->central->status);
	pthread_mutex_lock(philo->central->write);
	printf("All philosophers are full\n");
	pthread_mutex_unlock(philo->central->write);
	pthread_mutex_unlock(philo->central->eat);
	// pthread_mutex_unlock(philo->central->full);
	return ((void *) NULL);
}

void	*philosopher_died(t_philo *philo)
{
	pthread_mutex_lock(philo->central->status);
	philo->central->state = DEAD;
	pthread_mutex_unlock(philo->central->status);
	usleep(500);
	pthread_mutex_lock(philo->central->write);
	printf("%lld %d died\n",
	get_time_mseconds() - philo->central->start_time, philo->ID);
	pthread_mutex_unlock(philo->central->write);
	pthread_mutex_unlock(philo->central->eat);
	return ((void *) NULL);
}

void	*direct(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (check_status(philo) == ALIVE)// && check_full(philo) == 0)
	{
		usleep(500);
		pthread_mutex_lock(philo->central->eat);
		if ((get_time_mseconds() - philo->last_eaten) > philo->central->time_to_die && check_status(philo) == ALIVE)
			return (philosopher_died(philo));
		pthread_mutex_unlock(philo->central->eat);
		if (check_full(philo) == 1 && check_status(philo) == ALIVE)
			return (philosophers_full(philo));
	}
	
	return ((void *) NULL);
}
