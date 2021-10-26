/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   director.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 13:14:35 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/26 11:29:16 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <stdio.h>
#include <unistd.h>

#include <stdlib.h>
void    *philosophers_full(t_philo *philo)
{
    philo->central->state = 0;
    pthread_mutex_lock(philo->central->write);
    printf("All philosophers are full\n");
    pthread_mutex_unlock(philo->central->write);
    return (NULL);
}

void    *philosopher_died(t_philo *philo)
{
    philo->central->state = 0;
    usleep(500);
    pthread_mutex_lock(philo->central->write);
    printf("%lld %zu died\n", get_time_mseconds() - philo->central->start_time, philo->ID);
    pthread_mutex_unlock(philo->central->write);
    pthread_mutex_unlock(philo->central->eat);
    return (NULL);
}

void    *direct(void *arg)
{
    t_philo *philo;

    philo = arg;
    while (philo->central->state == ALIVE)
    {
        pthread_mutex_lock(philo->central->eat);
        if ((get_time_mseconds() - philo->last_eaten) > philo->central->time_to_die && philo->central->state == 1)
            return(philosopher_died(philo));
        pthread_mutex_unlock(philo->central->eat);
        if (philo->central->num_of_philo_full >= philo->central->num_of_philo && philo->central->state == 1)
            return (philosophers_full(philo));
    }
    return (NULL);
}
