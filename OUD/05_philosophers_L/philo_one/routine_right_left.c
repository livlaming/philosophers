/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_right_left.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 10:24:38 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/18 17:01:31 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <stdio.h>
void* routine_right_left(void *arg) 
{
    t_philo *philo;
    pthread_t manager;
    
    philo = arg;
    manager = NULL;
    philo->last_eaten = get_time_seconds();
    if (pthread_create(&manager, NULL, &manage, philo) != 0) // klopt het dat de manager ook een thread is of kan het ook een while loop zijn?
        return(NULL);
    while (philo->time_left > 0 && philo->info->state == ALIVE)
    {
        pthread_mutex_lock(philo->rfork);
        write_state("has taken a fork", philo, philo->ID);
        pthread_mutex_lock(philo->lfork);
        write_state("has taken a fork", philo, philo->ID);
        eating(philo);
        pthread_mutex_unlock(philo->rfork); //moeten deze eerder?
        pthread_mutex_unlock(philo->lfork); //moeten deze eerder?
        // philo->meals_left--;
        // if (philo->meals_left == 0)
        //     philo->info->num_of_philo_full++;
        write_state("is sleeping", philo, philo->ID);
        stupid_sleep(philo->info->time_to_sleep);
        write_state("is thinking", philo, philo->ID);
    }
        if (pthread_join(manager, NULL) != 0) // || return_val == (void*)NULL)
            return (NULL);
    return(NULL);
}