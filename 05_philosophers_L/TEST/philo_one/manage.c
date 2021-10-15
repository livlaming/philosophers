/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 13:30:14 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/15 19:37:10 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

void    *manage(void *arg)
{
    t_philo *philo;
    

    philo = arg;
    // long difference = get_time_seconds();
    // philo->last_eaten = get_time_seconds();
    while(philo->time_left > 0 && philo->info->state == 1)
    {
        // if (difference < (get_time_seconds() - philo->last_eaten))
        // {
        //     difference = (get_time_seconds() - philo->last_eaten);
        //     philo->time_left -= difference;
        // }
        philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
        if (philo->time_left <= 0 && philo->info->state == 1)
        {
            philo->info->state = 0;
            philo->time_left = 0;
            pthread_mutex_lock(philo->info->write);
            printf("%ld %zu died\n", get_time(philo->info->start_time), philo->ID);
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
    }
    return (NULL);
}
    // while(philo->info->state == 1 && philo->time_left > 0)
    // {
    //     // printf("time_left%ld\n", philo->time_left);
    //     // philo->time_left -= (get_time_seconds() - philo->last_eaten); ///DIT KLOPT NIET want hij doet nu elke loop het verschil van die twee naar beneden, 
    //     // printf("difference: %ld\n", (get_time_seconds() - philo->last_eaten));
    //     // if (philo->time_left <= 0 && philo->info->state == 1)
    //     // {
    //     if (difference < (get_time_seconds() - philo->last_eaten))
    //     {
    //         difference = (get_time_seconds() - philo->last_eaten);
    //         philo->time_left -= difference;
    //     }
    //     if (philo->time_left <= 0 && philo->info->state == 1)
    //     {
    //         pthread_mutex_lock(philo->info->write);
    //         philo->info->state = 0;
    //         philo->time_left = 0;
            
    //         printf("%ld %zu died\n", get_time(philo->info->start_time), philo->ID);
    //         pthread_mutex_unlock(philo->info->write);
    //         // write_state("died", philo, philo->ID);
    //         return ((void*)NULL);
    //     }
    //     if (philo->info->num_of_philo_full == philo->info->num_of_philo)
    //     {
    //         pthread_mutex_lock(philo->info->write);
    //         printf("All philosophers are full\n");
    //         pthread_mutex_unlock(philo->info->write);
    //         return ((void*)NULL);
    //     }
    // }
    // // return (philo);
    // return (NULL);
// }