/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 10:50:25 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/19 13:00:20 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

int check_input(int argc, char **argv)
{
    int i;

    i = 1;
    while (i < argc)
    {
        if (argv[i][0] < '0' || argv[i][0] > '9')
            return (-1);
        i++;
    }
    return (0);
}


int     join_thread(t_central *info, pthread_t *thread)
{
    int i;
    
    i = 0;
    while (i < info->num_of_philo)
    {
        if (pthread_join(thread[i], NULL) != 0)
            return (-1);
        i++;
    }
    return (0);
}

#include <stdio.h>
int create_threads(t_central *central, t_philo *philo, int i)
{
    pthread_t *thread;
    pthread_t *manager;

    thread = malloc(sizeof(pthread_t) * central->num_of_philo);
    manager = malloc(sizeof(pthread_t) * 1);
    while (i < central->num_of_philo)
    {
        if (i & 1) //even
        {
            if (pthread_create(&thread[i], NULL, &routine_even_right_left, &philo[i]) != 0)
                return(error_message(central, philo, 2));
        }
        else //odd
        {
            if (pthread_create(&thread[i], NULL, &routine_odd_left_right, &philo[i]) != 0)
                return(error_message(central, philo, 2));
        }
        // printf("Thread %d has started\n", i); //
        i++;
    }
    if (join_thread(central, thread) != 0)
        return(error_message(central, philo, 3));
    // pthread_mutex_destroy(&mutex);
    return (0);
}

int main(int argc, char **argv)
{
    t_central *central;
    t_philo *philo;

    philo = NULL;
    central = malloc(sizeof(t_central));
    if (!central)
        return (-1);
    if ((argc != 5 && argc != 6) || check_input(argc, argv) == -1)
        return(error_message(central, philo, 1));
    if (init_central_struct(central, argv, argc) == -1)
        return(error_message(central, philo, 1));
    philo = malloc(sizeof(t_philo) * central->num_of_philo);
    if (!philo)
        return (-1);
    if (init_philo_struct(central, philo) == -1)
        return(error_message(central, philo, 1));
    if (create_threads(central, philo, 0) == -1)
        return (-1);
    //free philo && central
    return (0);
}