/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hulpfunc_REMOVE.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 11:45:12 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/19 12:05:37 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

int     print_cur_central_struct(t_central *central)
{
    int i = 0;
    // central//
    printf("central STRUCT!\n");
    
	printf("num_of_philo: %d\n", central->num_of_philo);
    printf("num_of_forks: %d\n", central->num_of_forks);
    printf("time_to_die: %llu\n", central->time_to_die);
    printf("time_to_eat: %llu\n", central->time_to_eat);
    printf("time_to_sleep: %llu\n", central->time_to_sleep);
    if (central->num_of_meals)
        printf("num_of_meals: %d\n", central->num_of_meals);
    while(i < central->num_of_forks && &central->forks[i])
    {
        // printf("thread %d\n", i + 1);
        // printf("forks: %pthread_mutex_t *", &central->forks[i]);
        i++;
    }
    printf("threads: %d\n", i);
    printf("start_time: %llu\n", central->start_time);
    printf("state: %d\n", central->state);
    printf("num_of_philo_full: %d\n", central->num_of_philo_full);
    return (0);
}

int     print_cur_philo_struct(t_philo *philo)
{   
    printf("\n");
    printf("PHILO STRUCT!\n");
    printf("------------------\n");
    printf("ID: %d\n", (int)philo->ID);
    printf("meals_left: %d\n", philo->meals_left);
    printf("last_eaten: %llu\n", philo->last_eaten);

    printf("------------------\n");
    return (0);
}