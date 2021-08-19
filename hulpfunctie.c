/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hulpfunctie.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/19 15:03:36 by livlamin      #+#    #+#                 */
/*   Updated: 2021/08/19 15:30:26 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

int     print_cur_struct(t_info *info, t_philo *philo)
{
    int i = 0;
    //INFO//
    printf("INFO STRUCT!\n");
    
	printf("num_of_philo: %d\n", info->num_of_philo);
    printf("num_of_forks: %d\n", info->num_of_forks);
    printf("time_to_die: %d\n", info->time_to_die);
    printf("time_to_eat: %d\n", info->time_to_eat);
    printf("time_to_sleep: %d\n", info->time_to_sleep);
    if (info->num_of_meals)
        printf("num_of_meals: %d\n", info->num_of_meals);
    while(i < info->num_of_forks)
    {
        printf("thread %d\n", i + 1);
        // printf("forks: %pthread_mutex_t *", &info->forks[i]);
        i++;
    }
    
    philo = NULL;
    // printf("PHILO STRUCT!");
    // i = 0;
    // while (i < info->num_of_philo)
    // {
    //     printf("ID: %d\n", philo[i].ID);
    //     // printf("%d\n", philo[i].lfork);
	//     // printf("%d\n",philo[i].rfork);
	//     // printf("time_left: %d\n",philo[i].time_left);
	//     // printf("state: %d\n",philo[i].state);
    //     i++;
    // }
    
	// // pthread_mutex_t *lfork;
	// // pthread_mutex_t *rfork;
    // printf("time_left: %d\n", philo->time_left);
    // printf("state: %d\n", philo->state);
    // printf("philo->info->num_of_philo: %d\n", philo->info->num_of_philo);

    return (0);
}