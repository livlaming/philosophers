/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 09:48:33 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/11 10:54:56 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>

void    write_state(char *str, t_philo *philo, int ID)
{
    pthread_mutex_lock(philo->write);
    // printf("%d %d died\n", get_time(philo->info->start_time), (int)philo[ID].ID);
    printf("%d %d %s\n", get_time(philo->info->start_time), (int)philo[ID].ID, str);
    pthread_mutex_unlock(philo->write);

}

void* manage(void *arg)
{
    t_philo *philo;
    int ID;

    philo = arg;
    ID = 0;
    while(1)
    {
        while (ID < philo->info->num_of_philo)
        {
            get_time(philo[ID].time_left);
            if (philo[ID].time_left <= 0 && philo[ID].state == ALIVE)
            {
                philo[ID].state = DEAD;
                // char *str = malloc(5);
                // str = "died";
                write_state("died", philo, ID);
                // pthread_mutex_lock(philo->write);
                // printf("%d %d died\n", get_time(philo->info->start_time), (int)philo[ID].ID);
                // pthread_mutex_unlock(philo->write);
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
    return (philo);
}