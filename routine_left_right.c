/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_left_right.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 10:22:41 by livlamin      #+#    #+#                 */
/*   Updated: 2021/09/16 15:56:08 by livlamin      ########   odam.nl         */
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
        pthread_mutex_lock(philo->lfork);
        printf("%d %d has taken a fork\n", get_time(philo->info->start_time), (int)philo->ID);
        pthread_mutex_lock(philo->rfork);
        printf("%d %d has taken a fork\n", get_time(philo->info->start_time), (int)philo->ID);
        printf("%d %d is eating\n", get_time(philo->info->start_time), (int)philo->ID);
        stupid_sleep(philo->info->time_to_eat);
        philo->last_eaten = get_time(philo->info->start_time);
        philo->time_left = philo->info->time_to_die;
        if (philo->meals_left > 0)
            philo->meals_left--;
        if (philo->meals_left == 0)
            philo->info->num_of_philo_full++;
        pthread_mutex_unlock(philo->lfork);
        pthread_mutex_unlock(philo->rfork);
        philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
        printf("%d %d is sleeping\n", get_time(philo->info->start_time), (int)philo->ID);
        stupid_sleep(philo->info->time_to_sleep);
        philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
        printf("%d %d is thinking\n", get_time(philo->info->start_time), (int)philo->ID);
        philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
    }
    return((void*)philo->ID);
}



// void* routine_left_right(void *arg) 
// {
//     t_philo *philo;

//     philo = arg;
//     while(philo->time_left > 0)
//     {
//         pthread_mutex_lock(philo->lfork);
//         printf("%d %d has taken a fork\n", get_time(philo->info->start_time), (int)philo->ID);
//         pthread_mutex_lock(philo->rfork);
//         printf("%d %d has taken a fork\n", get_time(philo->info->start_time), (int)philo->ID);
//         printf("%d %d is eating\n", get_time(philo->info->start_time), (int)philo->ID);
//         pthread_mutex_lock(philo->info->eat);
//         stupid_sleep(philo->info->time_to_eat);
//         philo->last_eaten = get_time(philo->info->start_time);
//         if (philo->meals_left != -1)
//             philo->meals_left--;
//         if (philo->meals_left == 0)
//             philo->info->num_of_philo_full++;
//         if (philo->info->num_of_meals != -1 && philo->info->num_of_philo_full == philo->info->num_of_philo)
//         {
//             philo->state = DEAD;
//             printf("%d %d died\n", get_time(philo->info->start_time), (int)philo->ID);
//             pthread_mutex_unlock(philo->info->eat);
//             pthread_mutex_unlock(philo->lfork);
//             pthread_mutex_unlock(philo->rfork);
//             return((void*)philo->ID);
//         }
//         pthread_mutex_unlock(philo->info->eat);
//         pthread_mutex_unlock(philo->rfork);
//         pthread_mutex_unlock(philo->lfork);
//         // if (get_time(philo->info->start_time) - philo->last_eaten > philo->time_left)
//         // {
//         //     philo->state = DEAD;
//         //     printf("%d %d died\n", get_time(philo->info->start_time), (int)philo->ID);
//         //     return((void*)philo->ID);
//         // }
//         printf("%d %d is sleeping\n", get_time(philo->info->start_time), (int)philo->ID);
//         stupid_sleep(philo->info->time_to_sleep);
//         // if (get_time(philo->info->start_time) - philo->last_eaten > philo->time_left)
//         // {
//         //     philo->state = DEAD;
//         //     printf("%d %d died\n", get_time(philo->info->start_time), (int)philo->ID);
//         //     return((void*)philo->ID);
//         // }
//         printf("%d %d is thinking\n", get_time(philo->info->start_time), (int)philo->ID);
//     }
//     return((void*)philo->ID);
//     // return(NULL);
// }