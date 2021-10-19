/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eating.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 12:52:55 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/19 16:05:50 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void   eating(t_philo *philo)
{
    pthread_mutex_lock(philo->central->eat);
    if (philo->central->state == ALIVE)
    {
        write_state("is eating", philo, philo->ID);
        pthread_mutex_unlock(philo->central->eat);
        philo->last_eaten = get_time_mseconds();
        stupid_sleep(philo->central->time_to_eat);
        philo->meals_left--;
        if (philo->meals_left == 0)
            philo->central->num_of_philo_full++;
    }
    pthread_mutex_unlock(philo->central->eat);
}