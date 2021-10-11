/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 13:30:14 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/11 14:23:54 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>

void    *manage(void *arg)
{
    t_philo *philo;

    philo = arg;
    while(philo->time_left > 0)
    {
        // printf("1: time left %d\n", philo->time_left);
        philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
        // printf("start time: %d\n", get_time(philo->info->start_time));
        // printf("last_eaten: %d\n", get_time(philo->last_eaten));
        // printf("2: time left %d\n", philo->time_left);
        if (philo->time_left <= 0 && philo->state == ALIVE)
        {
            philo->state = DEAD;
            write_state("died", philo, philo->ID);
            return ((void*)NULL);
        }
        if (philo->info->num_of_philo_full == philo->info->num_of_philo)
        {
            write_state("All philosophers are full", NULL, 0);
            return (philo);
        }
    }
    return (philo);
}