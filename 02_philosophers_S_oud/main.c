/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/16 13:27:05 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/08 14:12:52 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

// ./philo_one number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]

int error_message(t_info *info, t_philo *philo, int error)
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

int     join_thread(void *ID, t_info *info, pthread_t *thread)
{
    int i;
    
    i = 0;
    while (i < info->num_of_philo)
    {
        if (pthread_join(thread[i], &ID) != 0)
            return (2);
        if ((int)&ID != 0)
            return(-1);
        i++;
    }
    return (0);
}

void* manage(void *arg)
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
                pthread_mutex_lock(philo->info->write);
                printf("%d %d died\n", get_time(philo->info->start_time), (int)philo[ID].ID);
                pthread_mutex_unlock(philo->info->write);
                // pthread_mutex_unlock(&philo->manage);
                return (philo);
            }
            if (philo->info->num_of_philo_full == philo->info->num_of_philo)
            {
                pthread_mutex_lock(philo->info->write);
                printf("All philosophers are full\n");
                pthread_mutex_unlock(philo->info->write);
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

int create_threads(t_info *info, t_philo *philo, int i)
{
    pthread_t *thread;
    pthread_t *manager;
    void *ID;
    
    ID = NULL;
    thread = malloc(sizeof(pthread_t) * info->num_of_philo);
    manager = malloc(sizeof(pthread_t) * 1);
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
    if (pthread_create(manager, NULL, &manage, philo) != 0) // klopt het dat de manager ook een thread is of kan het ook een while loop zijn?
        return(error_message(info, philo, 2));
    i = join_thread(ID, info, thread); //moet hier manager ook gejoint?
    if (i != 0)
        return (i);
    // pthread_mutex_destroy(&mutex);
    return (0);
}	



int check_input(int argc, char **argv)
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
