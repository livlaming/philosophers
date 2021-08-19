/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/16 13:27:05 by livlamin      #+#    #+#                 */
/*   Updated: 2021/08/19 16:56:47 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>

// number_of_philosophers 
// time_to_die 
// time_to_eat 
// time_to_sleep 
// [number_of_times_each_philosopher_must_eat]



// ◦ timestamp_in_ms X has taken a fork 
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died

// int mails = 0;
pthread_mutex_t mutex;

int     get_time()
{
    struct timeval  tv;
    int time_in_mill;

    time_in_mill = 0;
    gettimeofday(&tv, NULL);
    time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ; // sec to millisec
    return (0);
}

void* routine(void *philo) 
{
    // for (int i = 0; i < 10; i++) {
        // pthread_mutex_lock(philo->lfork);
        if (print_cur_philo_struct(philo) == -1)
            printf("Error");
        // philo = NULL;
        printf("hallo\n");
        // mails++;
        // struct timeval  tv;
        // gettimeofday(&tv, NULL);
        // int time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ; // sec to millisec
        // printf("%d X has taken a fork\n", time_in_mill);
        // printf("%d X is eating\n", time_in_mill);
        // printf("%d X is sleeping\n", time_in_mill);
        // printf("%d X died\n", time_in_mill);
        // pthread_mutex_unlock(&mutex);
    // printf("routine\n");
    
    
        // return (-1);
    return(NULL);
}

int create_threads(t_info *info, t_philo *philo)
{
    pthread_t *thread;
    int i;

    thread = malloc(sizeof(pthread_t) * info->num_of_philo);
    i = 0;
    // philo = NULL; // 
    // pthread_mutex_init(&mutex, NULL);
    while (i < info->num_of_philo)
    {
        if (pthread_create(&thread[i], NULL, &routine, &philo[i]) != 0)
        {
            perror("Failed to create thread");
            return 1;
        }
        printf("Thread %d has started\n", i);
        i++;
    }
    i = 0;
    while (i < info->num_of_philo)
    {
        if (pthread_join(thread[i], NULL) != 0)
            return 2;
        printf("Thread %d has finished execution\n", i);
        i++;
    }
    // pthread_mutex_destroy(&mutex);
    // printf("Number of mails: %d\n", mails);
    return (0);
}

int error_message(t_info *info, t_philo *philo, int error)
{
    if (error == 1)
        write(1, "Invalid input\n", 14);
    // free(philo->forks);?
    //check for mallocs, 
    free(info);
    free(philo);
    return (-1);
}

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
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_of_forks);
    while(i < info->num_of_forks)
    {
        pthread_mutex_init(&info->forks[i], NULL);
        i++;
    }
	info->start_time = get_time();
    return(0);
}

int init_philo_struct(t_info *info, t_philo *philo)
{
    int ID;

    ID = 0;
    while (ID < info->num_of_philo)
    {
        philo[ID].ID = ID + 1;
	    philo[ID].lfork = &info->forks[ID];
	    philo[ID].rfork = &info->forks[ID + 1];
	    philo[ID].time_left = info->time_to_die;
	    philo[ID].state = ALIVE;
	    philo[ID].info = info;
        // print_cur_philo_struct(&philo[ID]);
        ID++;
    }
    return (0);
}			

int check_input(int argc, char **argv)
{
    int i;

    i = 0;
    while (i < argc)
    {
        if (argv[i][0] == '-')
            return(-1);
        i++;
    }
    return (0);
}

int main(int argc, char **argv) 
{
    t_info *info;
    t_philo *philo;
    
    info = malloc(sizeof(t_info));
    if (!info)
        return (-1);
    philo = NULL;
    if ((argc != 5 && argc != 6) || check_input(argc, argv) == -1)
        return(error_message(info, philo, 1));
    if (init_info_struct(info, argv, argc) == -1)
        return(error_message(info, philo, 1));
    philo = malloc(sizeof(t_philo) * info->num_of_philo);
    if (!philo)
        return (-1);
    if (init_philo_struct(info, philo) == -1)
        return(error_message(info, philo, 1));
    // if (print_cur_info_struct(info) == -1 || print_cur_philo_struct(philo) == -1)
    //     return (-1);
    if (create_threads(info, philo) == -1)
        return (-1);  
    free(philo); 
    free(info);
    return (0);
}