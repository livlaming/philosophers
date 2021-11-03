/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eating.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 12:52:55 by livlamin      #+#    #+#                 */
/*   Updated: 2021/11/03 15:34:33 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating_left_right(t_philo *philo)
{
	if (check_status(philo) == ALIVE)
	{
		pthread_mutex_lock(philo->central->eat);
		philo->last_eaten = get_time_mseconds();
		write_state("is eating", philo, philo->ID);		
		pthread_mutex_unlock(philo->central->eat);
		stupid_sleep(philo->central->time_to_eat);
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
		philo->meals_left--;
		pthread_mutex_lock(philo->central->full);
		if (philo->meals_left == 0)
			philo->central->num_of_philo_full++;
		pthread_mutex_unlock(philo->central->full);
	}
	else
	{
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
		// pthread_mutex_unlock(philo->central->eat);
		
	}
	
}


void	eating_right_left(t_philo *philo)
{
	
	if (check_status(philo) == ALIVE)
	{
		pthread_mutex_lock(philo->central->eat);
		philo->last_eaten = get_time_mseconds();
		write_state("is eating", philo, philo->ID);
		pthread_mutex_unlock(philo->central->eat);
		stupid_sleep(philo->central->time_to_eat);
		pthread_mutex_unlock(philo->rfork);
		pthread_mutex_unlock(philo->lfork);
		philo->meals_left--;
		pthread_mutex_lock(philo->central->full);
		if (philo->meals_left == 0)
			philo->central->num_of_philo_full++;
		pthread_mutex_unlock(philo->central->full);	
	}
	else
	{
		pthread_mutex_unlock(philo->rfork);
		pthread_mutex_unlock(philo->lfork);
		// pthread_mutex_unlock(philo->central->eat);
		
	}
	
}
 