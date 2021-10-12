/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_right_left.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 10:24:38 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/12 10:00:05 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <stdio.h>
void* routine_right_left(void *arg) 
{
    t_philo *philo;
    pthread_t manager;
    void *return_val = NULL;
    
    philo = arg;
    manager = NULL;
    if (pthread_create(&manager, NULL, &manage, philo) != 0) // klopt het dat de manager ook een thread is of kan het ook een while loop zijn?
        return ((void*)philo->ID); //
    while (philo->time_left > 0 && philo->state == ALIVE)
    {
        pthread_mutex_lock(philo->rfork);
        write_state("has taken a fork", philo, philo->ID);
        pthread_mutex_lock(philo->lfork);
        write_state("has taken a fork", philo, philo->ID);
        eating(philo);
        philo->meals_left--;
        if (philo->meals_left == 0)
            philo->info->num_of_philo_full++;
        pthread_mutex_unlock(philo->rfork); //moeten deze eerder?
        pthread_mutex_unlock(philo->lfork); //moeten deze eerder?
        write_state("is sleeping", philo, philo->ID);
        stupid_sleep(philo->info->time_to_sleep);
        write_state("is thinking", philo, philo->ID);
    }
    while (philo->state == ALIVE)
    {
        if (pthread_join(manager, return_val) != 0 || return_val == (void*)NULL)
            return ((void*)philo->ID);
    }
    return((void*)philo->ID);
}