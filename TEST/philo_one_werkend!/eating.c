/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eating.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 12:52:55 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/21 11:04:32 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void   eating(t_philo *philo)
{
    pthread_mutex_lock(philo->central->eat);
    if (philo->central->state == ALIVE)
    {
        write_state("is eating", philo, philo->ID);
        philo->last_eaten = get_time_mseconds();
        pthread_mutex_unlock(philo->central->eat);
        stupid_sleep(philo->central->time_to_eat);
        philo->meals_left--;
        if (philo->meals_left == 0)
            philo->central->num_of_philo_full++;
    }
    else
    {
        pthread_mutex_unlock(philo->rfork); //moeten deze eerder?
        pthread_mutex_unlock(philo->lfork); //moeten deze eerder?
        pthread_mutex_unlock(philo->central->eat);
    }  
}