/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_right_left.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 10:24:38 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/11 09:42:28 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

#include <stdlib.h>

static void* manage(void *arg)
{
    t_philo *philo;
    int ID;

    philo = arg;
    ID = 0;
    // pthread_mutex_lock(&philo->manage);
    while(1)
    {
        while (ID < philo->info->num_of_philo)
        {
            get_time(philo[ID].time_left);
            if (philo[ID].time_left <= 0 && philo[ID].state == ALIVE)
            {
                philo[ID].state = DEAD;
                pthread_mutex_lock(philo->write);
                printf("%d %d died\n", get_time(philo->info->start_time), (int)philo[ID].ID);
                pthread_mutex_unlock(philo->write);
                // pthread_mutex_unlock(&philo->manage);
                return (philo);
            }
            if (philo->info->num_of_philo_full == philo->info->num_of_philo)
            {
                pthread_mutex_lock(philo->write);
                printf("All philosophers are full\n");
                pthread_mutex_unlock(philo->write);
                // pthread_mutex_unlock(&philo->manage);
                return (philo);
            }
            ID++;
        }
        ID = 0;
    }
    // pthread_mutex_unlock(&philo->manage);
    return (philo);
}

void* routine_right_left(void *arg) 
{
    t_philo *philo;
    pthread_t manager;

    philo = arg;
    manager = NULL;
    if (pthread_create(&manager, NULL, &manage, philo) != 0) // klopt het dat de manager ook een thread is of kan het ook een while loop zijn?
        return((void*)philo->ID); //
        // return(error_message(info, philo, 2));
    while(philo->time_left > 0)
    {
        philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
        pthread_mutex_lock(philo->rfork);
        printf("%d %d has taken a fork\n", get_time(philo->info->start_time), (int)philo->ID);
        pthread_mutex_lock(philo->lfork);
        printf("%d %d has taken a fork\n", get_time(philo->info->start_time), (int)philo->ID);
        printf("%d %d is eating\n", get_time(philo->info->start_time), (int)philo->ID);
        stupid_sleep(philo->info->time_to_eat);
        philo->last_eaten = get_time(philo->info->start_time);
        philo->time_left = philo->info->time_to_die;
        philo->meals_left--;
        if (philo->meals_left == 0)
            philo->info->num_of_philo_full++;
        pthread_mutex_unlock(philo->rfork); //moeten deze eerder?
        pthread_mutex_unlock(philo->lfork); //moeten deze eerder?
        philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
        printf("%d %d is sleeping\n", get_time(philo->info->start_time), (int)philo->ID);
        stupid_sleep(philo->info->time_to_sleep);
        philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
        printf("%d %d is thinking\n", get_time(philo->info->start_time), (int)philo->ID);
        philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
    }
    if (pthread_join(manager, NULL) != 0)
        return (NULL);
    return((void*)philo->ID);
}