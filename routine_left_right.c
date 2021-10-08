/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_left_right.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 10:22:41 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/08 16:10:11 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

#include <stdlib.h>

void* routine_left_right(void *arg) 
{
    t_philo *philo;

    philo = arg;
    while(philo->time_left > 0)
    {
        philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
        pthread_mutex_lock(philo->lfork);
        printf("%d %d has taken a fork\n", get_time(philo->info->start_time), (int)philo->ID);
        if (philo->info->num_of_philo == 1)
        {
            stupid_sleep(philo->info->time_to_die);
            philo->time_left = 0;
            pthread_mutex_unlock(philo->lfork);
            return((void*)philo->ID);
        }
        pthread_mutex_lock(philo->rfork);
        printf("%d %d has taken a fork\n", get_time(philo->info->start_time), (int)philo->ID);
        printf("%d %d is eating\n", get_time(philo->info->start_time), (int)philo->ID);
        stupid_sleep(philo->info->time_to_eat);
        philo->last_eaten = get_time(philo->info->start_time);
        philo->time_left = philo->info->time_to_die;   
        philo->meals_left--;
        if (philo->meals_left == 0)
            philo->info->num_of_philo_full++;
        pthread_mutex_unlock(philo->lfork); //moeten deze eerder?
        pthread_mutex_unlock(philo->rfork); //moeten deze eerder?
        philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
        printf("%d %d is sleeping\n", get_time(philo->info->start_time), (int)philo->ID);
        stupid_sleep(philo->info->time_to_sleep);
        philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
        printf("%d %d is thinking\n", get_time(philo->info->start_time), (int)philo->ID);
        philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
    }
    if (philo->time_left <= 0)
        philo->info->dead = 1;
    return((void*)philo->ID);
}
