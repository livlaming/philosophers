/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 13:30:14 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/18 17:30:56 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

void    *manage(void *arg)
{
    t_philo *philo;
    

    philo = arg;
    long difference = 0;
    // difference = (get_time_seconds() - philo->last_eaten);
    philo->last_eaten = get_time_seconds();
    while(philo->time_left > difference && philo->info->state == 1)
    {
        difference = (get_time_seconds() - philo->last_eaten);
        if (philo->time_left <= difference && philo->info->state == 1)
        {
            pthread_mutex_lock(philo->info->write);
            philo->info->state = 0;
            printf("differenc %ld", difference);
            pthread_mutex_unlock(philo->info->write);
            return ((void*)NULL);
            // philo->info->state = 0;
            // philo->time_left = 0;
            // // printf("%ld %zu died\n", get_time(philo->info->start_time), philo->ID);
            // write_state("died", philo, philo->ID);
            // philo->info->state = 0;
            // philo->time_left = 0;
            return ((void*)NULL);
        }
        if (philo->info->num_of_philo_full == philo->info->num_of_philo)
        {
            pthread_mutex_lock(philo->info->write);
            printf("All philosophers are full\n");
            pthread_mutex_unlock(philo->info->write);
            return ((void*)NULL);
        }
        difference = (get_time_seconds() - philo->last_eaten);
    }
    return (NULL);
}


//  pthread_mutex_lock(philo->info->write);
//     if (philo->info->state == 1)
//     {
//         if (!philo)
//             printf("%s\n", str);
//         else
//             printf("%ld %zu %s\n", get_time(philo->info->start_time), ID, str);
        
//     }
//     pthread_mutex_unlock(philo->info->write);

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