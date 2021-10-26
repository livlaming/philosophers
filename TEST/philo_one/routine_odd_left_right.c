/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_odd_left_right.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 12:32:01 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/26 13:07:57 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

static void	*one_philosopher(t_philo *philo)
{
	stupid_sleep(philo->central->time_to_die);
	write_state("died", philo, philo->ID);
	pthread_mutex_unlock(philo->lfork);
	return ((void *) NULL);
}

void	*routine_odd_left_right(void *arg)
{
	t_philo		*philo;
	pthread_t	director;

	philo = arg;
	director = NULL;
	if (pthread_create(&director, NULL, &direct, philo) != 0)
		return ((void *) NULL); // error?
	philo->last_eaten = get_time_mseconds();
	while (philo->central->state == ALIVE)
	{
		pthread_mutex_lock(philo->lfork);
		write_state("has taken a fork", philo, philo->ID);
		if (philo->central->num_of_philo == 1)
			return (one_philosopher(philo));
		pthread_mutex_lock(philo->rfork);
		write_state("has taken a fork", philo, philo->ID);
		eating(philo);
		write_state("is sleeping", philo, philo->ID);
		stupid_sleep(philo->central->time_to_sleep);
		write_state("is thinking", philo, philo->ID);
	}
	if (pthread_join(director, NULL) != 0)
		return ((void *) NULL);// error?
	return ((void *) NULL);
}
