/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_even_right_left.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 12:58:27 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/19 13:01:28 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void* routine_even_right_left(void *arg) 
{
    t_philo *philo;
    pthread_t manager;
    
    philo = arg;
    manager = NULL;
    // if (pthread_create(&manager, NULL, &manage, philo) != 0) // klopt het dat de manager ook een thread is of kan het ook een while loop zijn?
    //     return ((void*)philo->ID); //
    philo->last_eaten = get_time_mseconds();
    while (philo->central->state == ALIVE)
    {
        pthread_mutex_lock(philo->lfork);
        write_state("has taken a fork", philo, philo->ID);
        pthread_mutex_lock(philo->rfork);
        write_state("has taken a fork", philo, philo->ID);
        eating(philo);
        pthread_mutex_unlock(philo->lfork); //moeten deze eerder?
        pthread_mutex_unlock(philo->rfork); //moeten deze eerder?
        write_state("is sleeping", philo, philo->ID);
        stupid_sleep(philo->central->time_to_sleep);
        write_state("is thinking", philo, philo->ID);
    }
    // if (pthread_join(manager, NULL) != 0 || return_val == (void*)NULL)
    //     return ((void*)philo->ID);
    return((void*)NULL);
}