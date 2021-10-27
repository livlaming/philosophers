/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eating.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 12:52:55 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/27 12:11:39 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating_left_right(t_philo *philo)
{
	pthread_mutex_lock(philo->central->eat);
	if (philo->central->state == ALIVE)
	{
		write_state("is eating", philo, philo->ID);
		philo->last_eaten = get_time_mseconds();
		pthread_mutex_unlock(philo->central->eat);
		stupid_sleep(philo->central->time_to_eat);
		philo->meals_left--;
		if (philo->meals_left == 0)
			philo->central->num_of_philo_full++;
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
	}
	else
	{
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
		pthread_mutex_unlock(philo->central->eat);
	}
}


void	eating_right_left(t_philo *philo)
{
	pthread_mutex_lock(philo->central->eat);
	if (philo->central->state == ALIVE)
	{
		write_state("is eating", philo, philo->ID);
		philo->last_eaten = get_time_mseconds();
		pthread_mutex_unlock(philo->central->eat);
		stupid_sleep(philo->central->time_to_eat);
		philo->meals_left--;
		if (philo->meals_left == 0)
			philo->central->num_of_philo_full++;
		pthread_mutex_unlock(philo->rfork);
		pthread_mutex_unlock(philo->lfork);
	}
	else
	{
		pthread_mutex_unlock(philo->rfork);
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->central->eat);
	}
}