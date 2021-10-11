/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/16 13:27:05 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/11 11:52:10 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

// ./philo_one number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]

static int error_message(t_info *info, t_philo *philo, int error)
{
    if (error == 1)
        write(1, "Invalid input\n", 14);

    if (error == 2)
    {
        perror("Failed to create thread");
        write(1, "Failed to create thread\n", 24);
    }
    free(info); //uitgebreiden
    free(philo); //uitgebreiden
    return (-1);
}

static int     join_thread(void *ID, t_info *info, pthread_t *thread)
{
    int i;
    
    i = 0;
    while (i < info->num_of_philo)
    {
        if (pthread_join(thread[i], &ID) != 0)
            return (2);
        if ((size_t)&ID != 0)
            return(-1);
        i++;
    }
    return (0);
}

static int create_threads(t_info *info, t_philo *philo, int i)
{
    pthread_t *thread;
    void *ID;
    // int return_val = 0;
    
    ID = NULL;
    thread = malloc(sizeof(pthread_t) * info->num_of_philo);
    while (i < info->num_of_philo)
    {
        if (i & 1) //odd
        {
            if (pthread_create(&thread[i], NULL, &routine_right_left, &philo[i]) != 0)
                return(error_message(info, philo, 2));
        }
        else //even
        {
            if (pthread_create(&thread[i], NULL, &routine_left_right, &philo[i]) != 0)
                return(error_message(info, philo, 2));
        }
        // printf("Thread %d has started\n", i); //
        i++;
    }
    i = join_thread(ID, info, thread);
    // FREE MUTEX
    // pthread_mutex_destroy(&mutex);
    if (i != 0)
        return (i);
        // pthread_exit() ?
    return (0);
}

static int check_input(int argc, char **argv)
{
    int i;

    i = 1;
    while (i < argc)
    {
        if (argv[i][0] <= '0' || argv[i][0] >= '9')
            return (-1);
        i++;
    }
    return (0);
}

int main(int argc, char **argv) 
{
    t_info *info;
    t_philo *philo;
    
    philo = NULL;
    info = malloc(sizeof(t_info));
    if (!info)
        return (-1);
    if ((argc != 5 && argc != 6) || check_input(argc, argv) == -1)
        return(error_message(info, philo, 1));
    if (init_info_struct(info, argv, argc) == -1)
        return(error_message(info, philo, 1));
    philo = malloc(sizeof(t_philo) * info->num_of_philo);
    if (!philo)
        return (-1);
    if (init_philo_struct(info, philo) == -1)
        return(error_message(info, philo, 1));
    if (create_threads(info, philo, 0) == -1)
        return (-1);  
    free(philo); // uitgebreider!
    free(info); //uitgebreider!
    return (0);
}
