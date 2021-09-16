/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_right_left.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 10:24:38 by livlamin      #+#    #+#                 */
/*   Updated: 2021/09/16 15:05:01 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

void* routine_right_left(void *arg) 
{
    t_philo *philo;

    philo = arg;
    while(philo->time_left > 0)
    {
        pthread_mutex_lock(philo->rfork);
        printf("%d %d has taken a fork\n", get_time(philo->info->start_time), (int)philo->ID);
        pthread_mutex_lock(philo->lfork);
        printf("%d %d has taken a fork\n", get_time(philo->info->start_time), (int)philo->ID);
        printf("%d %d is eating\n", get_time(philo->info->start_time), (int)philo->ID);
        stupid_sleep(philo->info->time_to_eat);
        philo->last_eaten = get_time(philo->info->start_time);
        if (philo->meals_left > 0)
            philo->meals_left--;
        if (philo->meals_left == 0)
            philo->info->num_of_philo_full++;
        pthread_mutex_unlock(philo->rfork);
        pthread_mutex_unlock(philo->lfork);
        philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
        printf("%d %d is sleeping\n", get_time(philo->info->start_time), (int)philo->ID);
        stupid_sleep(philo->info->time_to_sleep);
        philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
        printf("%d %d is thinking\n", get_time(philo->info->start_time), (int)philo->ID);
        philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
    }
    return((void*)philo->ID);
}