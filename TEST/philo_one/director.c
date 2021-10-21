/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   director.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 13:14:35 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/21 12:32:56 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <stdio.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

void    *direct(void *arg)
{
    t_philo *philo;

    philo = arg;
    while (philo->central->state == ALIVE)
    {
        pthread_mutex_lock(philo->central->eat);
        if ((get_time_mseconds() - philo->last_eaten) > philo->central->time_to_die && philo->central->state == 1)
        {
            philo->central->state = 0;
            usleep(500);
            pthread_mutex_lock(philo->central->write);
            printf("%lld %zu died\n", get_time_mseconds() - philo->central->start_time, philo->ID);
            pthread_mutex_unlock(philo->central->write);
            pthread_mutex_unlock(philo->central->eat);
            return(NULL);
        }
        pthread_mutex_unlock(philo->central->eat);
        if (philo->central->num_of_philo_full == philo->central->num_of_philo && philo->central->state == 1)
        {
            philo->central->state = 0;
            pthread_mutex_lock(philo->central->write);
            printf("All philosophers are full\n");
            pthread_mutex_unlock(philo->central->write);
            return (NULL);
        }
    }
    return (NULL);
}
