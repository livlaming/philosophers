/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 13:30:14 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/11 13:39:31 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>

void    *manage(void *arg)
{
    t_philo *philo;

    philo = arg;
    while(1)
    {
        printf("time left %d\n", philo->time_left);
        philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
        printf("time left %d\n", philo->time_left);
        if (philo->time_left <= 0 && philo->state == ALIVE)
        {
            philo->state = DEAD;
            write_state("died", philo, philo->ID);
            return (philo);
        }
        if (philo->info->num_of_philo_full == philo->info->num_of_philo)
        {
            write_state("All philosophers are full", NULL, 0);
            return (philo);
        }
    }
    return (philo);
}