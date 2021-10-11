/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_left_right.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 10:22:41 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/11 11:53:25 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>

// void   eating(t_philo *philo)
// {
//     pthread_mutex_lock(philo->info->eat);
//     write_state("is eating", philo, philo->ID);
//     stupid_sleep(philo->info->time_to_eat);
//     philo->last_eaten = get_time(philo->info->start_time);
//     // pthread_mutex_unlock(philo->lfork); //moeten deze eerder?
//     // pthread_mutex_unlock(philo->rfork); //moeten deze eerder?
//     philo->time_left = philo->info->time_to_die;
//     pthread_mutex_unlock(philo->info->eat);

// }

void* routine_left_right(void *arg) 
{
    t_philo *philo;
    pthread_t manager;

    philo = arg;
    manager = NULL;
    if (pthread_create(&manager, NULL, &manage, philo) != 0) // klopt het dat de manager ook een thread is of kan het ook een while loop zijn?
        return (NULL); //
        // return(error_message(info, philo, 2));
    while(philo->time_left > 0)
    {
        // philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
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
        // eating(philo);
        // write_state("is eating", philo, philo->ID);
        // stupid_sleep(philo->info->time_to_eat);
        // philo->last_eaten = get_time(philo->info->start_time);
        pthread_mutex_unlock(philo->lfork); //moeten deze eerder?
        pthread_mutex_unlock(philo->rfork); //moeten deze eerder?
        printf("time left = %d", philo->time_left);
        // philo->time_left = philo->info->time_to_die; 
        philo->meals_left--;
        if (philo->meals_left == 0)
            philo->info->num_of_philo_full++;
        // philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
        write_state("is sleeping", philo, philo->ID);
        stupid_sleep(philo->info->time_to_sleep);
        // philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
        write_state("is thinking", philo, philo->ID);
        // philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
    }
    if (pthread_join(manager, NULL) != 0)
            return (NULL);
    return((void*)philo->ID);
}
