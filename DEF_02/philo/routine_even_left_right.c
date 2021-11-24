/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_even_left_right.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 12:32:01 by livlamin      #+#    #+#                 */
/*   Updated: 2021/11/24 10:13:39 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	*routine_even_left_right(void *arg)
{
	t_philo		*philo;
	pthread_t	director;

	philo = arg;
	director = NULL;
	pthread_mutex_lock(philo->central->eat);
	philo->last_eaten = get_time_mseconds();
	pthread_mutex_unlock(philo->central->eat);
	if (pthread_create(&director, NULL, &direct, philo) != 0)
		return (error_message_2(1));
	while (check_status(philo) == ALIVE)
	{
		pthread_mutex_lock(philo->lfork);
		write_state("has taken a fork", philo, philo->ID);
		pthread_mutex_lock(philo->rfork);
		write_state("has taken a fork", philo, philo->ID);
		eating_left_right(philo);
		write_state("is sleeping", philo, philo->ID);
		stupid_sleep(philo->central->time_to_sleep);
		write_state("is thinking", philo, philo->ID);
		usleep(1000);
	}
	if (pthread_join(director, NULL) != 0)
		return (error_message_2(2));
	return ((void *) NULL);
}
