/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eating.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 12:52:55 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/29 13:55:27 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating_left_right(t_philo *philo)
{
	pthread_mutex_lock(philo->central->eat);
	if (check_status(philo) == 1)
	{
		write_state("is eating", philo, philo->ID);
		philo->last_eaten = get_time_mseconds();
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
	}
	pthread_mutex_unlock(philo->central->eat);
}


void	eating_right_left(t_philo *philo)
{
	pthread_mutex_lock(philo->central->eat);
	if (check_status(philo) == 1)
	{
		write_state("is eating", philo, philo->ID);
		philo->last_eaten = get_time_mseconds();
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
		
	}
	pthread_mutex_unlock(philo->central->eat);
}