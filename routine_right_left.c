/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_right_left.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 10:24:38 by livlamin      #+#    #+#                 */
/*   Updated: 2021/09/13 13:44:48 by livlamin      ########   odam.nl         */
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
        pthread_mutex_lock(philo->info->eat);
        stupid_sleep(philo->info->time_to_eat);
        philo->last_eaten = get_time(philo->info->start_time);
        if (philo->meals_left != -1)
            philo->meals_left--;
        if (philo->meals_left == 0)
            philo->info->num_of_philo_full++;
        if (philo->info->num_of_meals != -1 && philo->info->num_of_philo_full == philo->info->num_of_philo)
        {
            printf("%d %d died\n", get_time(philo->info->start_time), (int)philo->ID);
            pthread_mutex_unlock(philo->info->eat);
            pthread_mutex_unlock(philo->lfork);
            pthread_mutex_unlock(philo->rfork);
            return((void*)philo->ID);
        }
        pthread_mutex_unlock(philo->info->eat);
        pthread_mutex_unlock(philo->rfork);
        pthread_mutex_unlock(philo->lfork);
        {
            printf("%d %d died\n", get_time(philo->info->start_time), (int)philo->ID);
            return((void*)philo->ID);
        }
        printf("%d %d is sleeping\n", get_time(philo->info->start_time), (int)philo->ID);
        stupid_sleep(philo->info->time_to_sleep);
        if (get_time(philo->info->start_time) - philo->last_eaten > philo->time_left)
        {
            printf("%d %d died\n", get_time(philo->info->start_time), (int)philo->ID);
            return((void*)philo->ID);
        }
            
        printf("%d %d is thinking\n", get_time(philo->info->start_time), (int)philo->ID);
        
    }
    return((void*)philo->ID);
    // return(NULL);
}