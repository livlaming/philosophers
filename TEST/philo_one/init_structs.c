/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_structs.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/24 17:43:57 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/19 15:43:22 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

int init_philo_struct(t_central *central, t_philo *philo)
{
    int ID;

    ID = 0;
    while (ID < central->num_of_philo)
    {
        philo[ID].ID = ID + 1;
	    philo[ID].lfork = &central->forks[ID];
        if (ID == central->num_of_philo - 1)
            philo[ID].rfork = &central->forks[0];
        else
	        philo[ID].rfork = &central->forks[ID + 1];
        philo[ID].last_eaten = central->start_time;
        philo[ID].meals_left = central->num_of_meals;
	    philo[ID].central = central;
        print_cur_philo_struct(&philo[ID]);
        ID++;
    }
    return (0);
}

int init_central_struct(t_central *central, char **argv, int argc)
{
    int i;
    
    i = 0;
    central->num_of_philo = ft_atoi(argv[1]);
    if (central->num_of_philo == 0)
        return(error_message(central, NULL, 1));
    central->num_of_forks = central->num_of_philo;
    central->time_to_die = ft_atoull(argv[2]);
	central->time_to_eat = ft_atoull(argv[3]);
	central->time_to_sleep = ft_atoull(argv[4]);
    if (argc == 6)
        central->num_of_meals = ft_atoi(argv[5]);
    else
        central->num_of_meals = -1;
	central->forks = malloc(sizeof(pthread_mutex_t) * central->num_of_forks);
    while(i < central->num_of_forks)
    {
        pthread_mutex_init(&central->forks[i], NULL);
        i++;
    }
	central->start_time = get_time_mseconds();
    central->eat = malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(central->eat, NULL);
    central->write = malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(central->write, NULL);
    central->status = malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(central->status, NULL);
    central->num_of_philo_full = 0;
    central->state = 1;
    print_cur_central_struct(central);
    return(0);
}

// int     destroy_structs()
// {
//     int i;

//     i = 0;
//     while(i < central->num_of_forks)
//     {
//         destroy_mutex(&central->forks[i], NULL);
//         i++;
//     }
// }


// void    destroy_mutex()//