/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   director.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 13:14:35 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/19 13:49:55 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <stdio.h>
#include <unistd.h>

void    *direct(void *arg)
{
    t_philo *philo;
    // unsigned long long difference = 0;

    philo = arg;
    while(philo->central->state == 1 && philo->central->num_of_philo_full != philo->central->num_of_philo)
    {
        // philo->time_left -= get_time_seconds() - philo->last_eaten;
        if ((get_time_mseconds() - philo->last_eaten) > philo->central->time_to_die && philo->central->state == 1)
        {
            pthread_mutex_lock(philo->central->eat);
            pthread_mutex_lock(philo->central->write);
            philo->central->state = 0;
            printf("%lld %zu died\n", get_time_mseconds() - philo->central->start_time, philo->ID);
            pthread_mutex_unlock(philo->central->write);
            pthread_mutex_unlock(philo->central->eat);
            return ((void*)NULL);
        }
        if (philo->central->num_of_philo_full == philo->central->num_of_philo)
        {
            pthread_mutex_lock(philo->central->write);
            printf("All philosophers are full\n");
            pthread_mutex_unlock(philo->central->write);
            return ((void*)NULL);
        }
    }
    // return (philo);
    return ((void*)NULL);
}