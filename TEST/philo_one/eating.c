/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eating.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 12:52:55 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/29 15:20:11 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating_left_right(t_philo *philo)
{
	pthread_mutex_lock(philo->central->eat);
	if (check_status(philo) == ALIVE)
	{
		philo->last_eaten = get_time_mseconds();
		write_state("is eating", philo, philo->ID);
		pthread_mutex_unlock(philo->central->eat);
		stupid_sleep(philo->central->time_to_eat);
		philo->meals_left--;
		pthread_mutex_lock(philo->central->full);
		if (philo->meals_left == 0)
			philo->central->num_of_philo_full++;
		pthread_mutex_unlock(philo->central->full);
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
	if (check_status(philo) == ALIVE)
	{
		philo->last_eaten = get_time_mseconds();
		write_state("is eating", philo, philo->ID);
		pthread_mutex_unlock(philo->central->eat);
		stupid_sleep(philo->central->time_to_eat);
		philo->meals_left--;
		pthread_mutex_lock(philo->central->full);
		if (philo->meals_left == 0)
			philo->central->num_of_philo_full++;
		pthread_mutex_unlock(philo->central->full);
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