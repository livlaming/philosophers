/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 13:30:14 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/12 09:55:52 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

void    *manage(void *arg)
{
    t_philo *philo;

    philo = arg;
    while(philo->time_left > 0 && philo->state == 1)
    {
        philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
        if (philo->time_left <= 0 && philo->state == 1)
        {
            philo->state = 0;
            philo->time_left = 0;
            pthread_mutex_lock(philo->info->write);
            printf("%d %zu died\n", get_time(philo->info->start_time), philo->ID);
            pthread_mutex_unlock(philo->info->write);
            // write_state("died", philo, philo->ID);
            return ((void*)NULL);
        }
        if (philo->info->num_of_philo_full == philo->info->num_of_philo)
        {
            pthread_mutex_lock(philo->info->write);
            printf("All philosophers are full\n");
            pthread_mutex_unlock(philo->info->write);
            return ((void*)NULL);
        }
        philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
    }
    // return (philo);
    return (NULL);
}