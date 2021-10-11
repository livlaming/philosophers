/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_right_left.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 10:24:38 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/11 12:36:04 by livlamin      ########   odam.nl         */
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

void* routine_right_left(void *arg) 
{
    t_philo *philo;
    pthread_t manager;
    void *return_val = 0;

    philo = arg;
    manager = NULL;
    // if (pthread_create(&manager, NULL, &manage, philo) != 0) // klopt het dat de manager ook een thread is of kan het ook een while loop zijn?
    //     return ((void*)-1); //
        // return(error_message(info, philo, 2));
    while(philo->time_left > 0)
    {
        printf("ja");
        philo->time_left--;
        // // philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
        // pthread_mutex_lock(philo->rfork);
        // write_state("has taken a fork", philo, philo->ID);
        // pthread_mutex_lock(philo->lfork);
        // write_state("has taken a fork", philo, philo->ID);
        // eating(philo);
        // // write_state("is eating", philo, philo->ID);
        // // stupid_sleep(philo->info->time_to_eat);
        // philo->last_eaten = get_time(philo->info->start_time);
        // pthread_mutex_unlock(philo->rfork); //moeten deze eerder?
        // pthread_mutex_unlock(philo->lfork); //moeten deze eerder?
        // // printf("time left = %d", philo->time_left);
        // // philo->time_left = philo->info->time_to_die; 
        // philo->meals_left--;
        // if (philo->meals_left == 0)
        //     philo->info->num_of_philo_full++;
        // philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
        // write_state("is sleeping", philo, philo->ID);
        // stupid_sleep(philo->info->time_to_sleep);
        // // philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
        // write_state("is thinking", philo, philo->ID);
        // // philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
        
    }
    // if (pthread_join(manager, return_val) != 0)
    //     return ((void*)-1);
    if (return_val != 0)
        return((void*)return_val);
    return((void*)philo->ID);
}


// void* routine_right_left(void *arg) 
// {
//     t_philo *philo;
//     pthread_t manager;

//     philo = arg;
//     manager = NULL;
//     if (pthread_create(&manager, NULL, &manage, philo) != 0) // klopt het dat de manager ook een thread is of kan het ook een while loop zijn?
//         return(NULL); //
        
//     while(philo->time_left > 0)
//     {
//         // philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
//         pthread_mutex_lock(philo->rfork);
//         printf("%d %d has taken a fork\n", get_time(philo->info->start_time), (int)philo->ID);
//         pthread_mutex_lock(philo->lfork);
//         printf("%d %d has taken a fork\n", get_time(philo->info->start_time), (int)philo->ID);
//         printf("%d %d is eating\n", get_time(philo->info->start_time), (int)philo->ID);
//         stupid_sleep(philo->info->time_to_eat);
//         philo->last_eaten = get_time(philo->info->start_time);
//         pthread_mutex_unlock(philo->rfork); //moeten deze eerder?
//         pthread_mutex_unlock(philo->lfork); //moeten deze eerder?
//         philo->time_left = philo->info->time_to_die;
//         philo->meals_left--;
//         if (philo->meals_left == 0)
//             philo->info->num_of_philo_full++;
//         // philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
//         printf("%d %d is sleeping\n", get_time(philo->info->start_time), (int)philo->ID);
//         stupid_sleep(philo->info->time_to_sleep);
//         // philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
//         printf("%d %d is thinking\n", get_time(philo->info->start_time), (int)philo->ID);
//         // philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
//     }
//     if (pthread_join(manager, NULL) != 0)
//         return (NULL);
//     return((void*)philo->ID);
// }


// void* routine_right_left(void *arg) 
// {
//     t_philo *philo;
//     pthread_t manager;

//     philo = arg;
//     manager = NULL;
//     if (pthread_create(&manager, NULL, &manage, philo) != 0) // klopt het dat de manager ook een thread is of kan het ook een while loop zijn?
//         return(NULL); //
        
//     while(philo->time_left > 0)
//     {
//         // philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
//         pthread_mutex_lock(philo->rfork);
//         printf("%d %d has taken a fork\n", get_time(philo->info->start_time), (int)philo->ID);
//         pthread_mutex_lock(philo->lfork);
//         printf("%d %d has taken a fork\n", get_time(philo->info->start_time), (int)philo->ID);
//         printf("%d %d is eating\n", get_time(philo->info->start_time), (int)philo->ID);
//         stupid_sleep(philo->info->time_to_eat);
//         philo->last_eaten = get_time(philo->info->start_time);
//         pthread_mutex_unlock(philo->rfork); //moeten deze eerder?
//         pthread_mutex_unlock(philo->lfork); //moeten deze eerder?
//         philo->time_left = philo->info->time_to_die;
//         philo->meals_left--;
//         if (philo->meals_left == 0)
//             philo->info->num_of_philo_full++;
//         // philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
//         printf("%d %d is sleeping\n", get_time(philo->info->start_time), (int)philo->ID);
//         stupid_sleep(philo->info->time_to_sleep);
//         // philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
//         printf("%d %d is thinking\n", get_time(philo->info->start_time), (int)philo->ID);
//         // philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
//     }
//     if (pthread_join(manager, NULL) != 0)
//         return (NULL);
//     return((void*)philo->ID);
// }