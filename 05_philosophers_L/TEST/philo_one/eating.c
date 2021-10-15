/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eating.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 14:29:03 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/15 17:33:59 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void   eating(t_philo *philo)
{
    if (philo->info->state == ALIVE)
    {
        pthread_mutex_lock(philo->info->eat);
        write_state("is eating", philo, philo->ID);
        stupid_sleep(philo->info->time_to_eat);
        philo->last_eaten = get_time(philo->info->start_time);
        philo->time_left = philo->info->time_to_die;
        philo->meals_left--;
        if (philo->meals_left == 0)
            philo->info->num_of_philo_full++;
        pthread_mutex_unlock(philo->info->eat);
    }
}