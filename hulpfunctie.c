/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hulpfunctie.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/19 15:03:36 by livlamin      #+#    #+#                 */
/*   Updated: 2021/08/24 12:59:42 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

int     print_cur_info_struct(t_info *info)
{
    int i = 0;
    // INFO//
    printf("INFO STRUCT!\n");
    
	printf("num_of_philo: %d\n", info->num_of_philo);
    printf("num_of_forks: %d\n", info->num_of_forks);
    printf("time_to_die: %d\n", info->time_to_die);
    printf("time_to_eat: %d\n", info->time_to_eat);
    printf("time_to_sleep: %d\n", info->time_to_sleep);
    if (info->num_of_meals)
        printf("num_of_meals: %d\n", info->num_of_meals);
    while(i < info->num_of_forks && &info->forks[i])
    {
        printf("thread %d\n", i + 1);
        // printf("forks: %pthread_mutex_t *", &info->forks[i]);
        i++;
    }
    return (0);
}

int     print_cur_philo_struct(t_philo *philo)
{   
    printf("\n");
    printf("PHILO STRUCT!\n");
    printf("------------------\n");
    printf("ID: %d\n", (int)philo->ID);
        // printf("%d\n", philo.lfork);
	    // printf("%d\n",philo.rfork);
	printf("time_left: %d\n",philo->time_left);
	printf("state: %d\n",philo->state);
    printf("philo->info->num_of_philo: %d\n", philo->info->num_of_philo);
    printf("time_to_die: %d\n", philo->info->time_to_die);
    printf("time_to_eat: %d\n", philo->info->time_to_eat);
    printf("time_to_sleep: %d\n", philo->info->time_to_sleep);
    printf("------------------\n");
    return (0);
}

// int     print_cur_all_philo_struct(t_philo *philo)
// {
//     int i = 0;
    
//     printf("PHILO STRUCT!");

//     while (i < 5)
//     {
//         printf("ID: %d\n", philo[i].ID);
//         // printf("%d\n", philo[i].lfork);
// 	    // printf("%d\n",philo[i].rfork);
// 	    printf("time_left: %d\n",philo[i].time_left);
// 	    printf("state: %d\n",philo[i].state);
//         i++;
//     }
//     printf("philo->info->num_of_philo: %d\n", philo->info->num_of_philo);
//     return (0);
// }