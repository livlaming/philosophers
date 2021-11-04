/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_structs.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/24 17:43:57 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/18 16:55:45 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

int init_philo_struct(t_info *info, t_philo *philo)
{
    int ID;

    ID = 0;
    while (ID < info->num_of_philo)
    {
        philo[ID].ID = ID + 1;
	    philo[ID].lfork = &info->forks[ID];
        if (ID == info->num_of_philo - 1)
            philo[ID].rfork = &info->forks[0];
        else
	        philo[ID].rfork = &info->forks[ID + 1];
	    philo[ID].time_left = info->time_to_die;
        philo[ID].last_eaten = info->start_time;
        philo[ID].meals_left = info->num_of_meals;
	    philo[ID].info = info;
        // philo[ID].start_time = get_time(0);
        print_cur_philo_struct(&philo[ID]);
        ID++;
    }
    return (0);
}
#include <stdio.h>

int init_info_struct(t_info *info, char **argv, int argc)
{
    int i;
    
    i = 0;
    info->num_of_philo = ft_atoi(argv[1]);
    info->num_of_forks = info->num_of_philo;
    info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        info->num_of_meals = ft_atoi(argv[5]);
    else
        info->num_of_meals = -1;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_of_forks);
    while(i < info->num_of_forks)
    {
        pthread_mutex_init(&info->forks[i], NULL);
        i++;
    }
	info->start_time = get_time_seconds();
    // info->start_time = get_time(0);
    // printf("START TIME: %ld\n", info->start_time);
    info->eat = malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(info->eat, NULL);
    info->write = malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(info->write, NULL);
    info->status = malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(info->status, NULL);
    info->num_of_philo_full = 0;
    info->state = 1;
    print_cur_info_struct(info);
    return(0);
}


// void    destroy_mutex()//