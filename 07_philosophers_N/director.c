/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   director.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 13:14:35 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/19 14:04:08 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <stdio.h>
#include <unistd.h>

void    *direct(void *arg)
{
    t_philo *philo;

    philo = arg;
    // while(philo->central->state == 1 && philo->central->num_of_philo_full != philo->central->num_of_philo)
    while(1)
    {
        pthread_mutex_lock(philo->central->eat);
        if ((get_time_mseconds() - philo->last_eaten) > philo->central->time_to_die && philo->central->state == 1)
        {
            philo->central->state = 0;
            pthread_mutex_lock(philo->central->write);
            printf("%lld %zu died\n", get_time_mseconds() - philo->central->start_time, philo->ID);
            pthread_mutex_unlock(philo->central->write);
            pthread_mutex_unlock(philo->central->eat);
            return ((void*)NULL);
        }
        pthread_mutex_unlock(philo->central->eat);
        if (philo->central->num_of_philo_full == philo->central->num_of_philo && philo->central->state == 1)
        {
            philo->central->state = 0;
            pthread_mutex_lock(philo->central->write);
            printf("All philosophers are full\n");
            pthread_mutex_unlock(philo->central->write);
            // pthread_mutex_unlock(philo->central->eat);
            return ((void*)NULL);
        }
        // pthread_mutex_unlock(philo->central->eat);
    }
    // return (philo);
    return ((void*)NULL);
}