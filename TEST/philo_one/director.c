/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   director.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 13:14:35 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/19 16:13:41 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <stdio.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

static void    unlock_forks(t_philo *philo)
{
    int i;

    i = 0;
    while(i < philo->central->num_of_forks)
    {
        pthread_mutex_unlock(&philo->central->forks[i]);
        pthread_mutex_destroy(&philo->central->forks[i]);
        i++;
    }
}

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
            pthread_mutex_unlock(philo->central->status);
            unlock_forks(philo);
            return ((void*)NULL);
        }
        pthread_mutex_unlock(philo->central->eat);
        if (philo->central->num_of_philo_full == philo->central->num_of_philo && philo->central->state == 1)
        {
            philo->central->state = 0;
            pthread_mutex_lock(philo->central->write);
            printf("All philosophers are full\n");
            pthread_mutex_unlock(philo->central->write);
            unlock_forks(philo);
            return ((void*)NULL);
        }
    }
    return ((void*)NULL);
}