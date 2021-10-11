/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_left_right.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 10:22:41 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/11 14:28:54 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

#include <stdlib.h>

void* routine_left_right(void *arg) 
{
    t_philo *philo;
    pthread_t manager;
    void *return_val = NULL;
    
    philo = arg;
    manager = NULL;
    if (pthread_create(&manager, NULL, &manage, philo) != 0) // klopt het dat de manager ook een thread is of kan het ook een while loop zijn?
        return ((void*)philo->ID); //
    while(philo->time_left > 0)
    {
        pthread_mutex_lock(philo->lfork);
        write_state("has taken a fork", philo, philo->ID);
        if (philo->info->num_of_philo == 1)
        {
            stupid_sleep(philo->info->time_to_die);
            philo->time_left = 0;
            pthread_mutex_unlock(philo->lfork);
            return((void*)philo->ID);
        }
        pthread_mutex_lock(philo->rfork);
        write_state("has taken a fork", philo, philo->ID);
        eating(philo);
        philo->meals_left--;
        if (philo->meals_left == 0)
            philo->info->num_of_philo_full++;
        pthread_mutex_unlock(philo->lfork); //moeten deze eerder?
        pthread_mutex_unlock(philo->rfork); //moeten deze eerder?
        philo->meals_left--;
        if (philo->meals_left == 0)
            philo->info->num_of_philo_full++;
        write_state("is sleeping", philo, philo->ID);
        stupid_sleep(philo->info->time_to_sleep);
        write_state("is thinking", philo, philo->ID);
    }
    if (pthread_join(manager, return_val) != 0 || return_val == NULL)
        return ((void*)philo->ID);
    return((void*)philo->ID);
}



// void* routine_left_right(void *arg) 
// {
//     t_philo *philo;
//     pthread_t manager;
//     void *return_val = NULL;
    
//     philo = arg;
//     manager = NULL;
//     if (pthread_create(&manager, NULL, &manage, philo) != 0) // klopt het dat de manager ook een thread is of kan het ook een while loop zijn?
//         return ((void*)philo->ID); //
//     while(philo->time_left > 0)
//     {
//         // philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
//         pthread_mutex_lock(philo->lfork);
//         write_state("has taken a fork", philo, philo->ID);
//         if (philo->info->num_of_philo == 1)
//         {
//             stupid_sleep(philo->info->time_to_die);
//             philo->time_left = 0;
//             pthread_mutex_unlock(philo->lfork);
//             return((void*)philo->ID);
//         }
//         pthread_mutex_lock(philo->rfork);
//         write_state("has taken a fork", philo, philo->ID);
//         write_state("is eating", philo, philo->ID);
//         stupid_sleep(philo->info->time_to_eat);
//         philo->last_eaten = get_time(philo->info->start_time);
//         // printf("JA: last_eaten: %d\n", philo->last_eaten);
//         philo->time_left = philo->info->time_to_die;   
//         philo->meals_left--;
//         if (philo->meals_left == 0)
//             philo->info->num_of_philo_full++;
//         pthread_mutex_unlock(philo->lfork); //moeten deze eerder?
//         pthread_mutex_unlock(philo->rfork); //moeten deze eerder?
//         // philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
//         write_state("is sleeping", philo, philo->ID);
//         stupid_sleep(philo->info->time_to_sleep);
//         // philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
//         write_state("is thinking", philo, philo->ID);
//         // philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
//     }
//     if (pthread_join(manager, &return_val) != 0)
//         return ((void*)philo->ID);
//     if (return_val == (void*)NULL)
//         return ((void*)return_val);
//     return((void*)philo->ID);
// }