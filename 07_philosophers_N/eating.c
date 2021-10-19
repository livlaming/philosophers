/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eating.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 12:52:55 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/19 13:46:43 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void   eating(t_philo *philo)
{
    if (philo->central->state == ALIVE)
    {
        pthread_mutex_lock(philo->central->eat);
        write_state("is eating", philo, philo->ID);
        philo->last_eaten = get_time_mseconds();
        stupid_sleep(philo->central->time_to_eat);
        // philo->last_eaten = get_time(philo->central->start_time);
        philo->last_eaten = get_time_mseconds();
        philo->meals_left--;
        if (philo->meals_left == 0)
            philo->central->num_of_philo_full++;
        pthread_mutex_unlock(philo->central->eat);
    }
}