/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/16 13:27:05 by livlamin      #+#    #+#                 */
/*   Updated: 2021/08/19 11:32:47 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>

int mails = 0;
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

void* routine() {
    // for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        mails++;
        struct timeval  tv;
        gettimeofday(&tv, NULL);
        int time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ; // sec to millisec
        printf("%d X has taken a fork\n", time_in_mill);
        printf("%d X is eating\n", time_in_mill);
        printf("%d X is sleeping\n", time_in_mill);
        printf("%d X died\n", time_in_mill);
        pthread_mutex_unlock(&mutex);
    return(NULL);
}

int create_threads_philo(t_info *philo)
{
    pthread_t *th;
    int i;

    i = 1;
    th = malloc(sizeof(pthread_t) * philo->num_of_philo);
    i = 0;
    pthread_mutex_init(&mutex, NULL);
    while (i < philo->num_of_philo)
    {
        if (pthread_create(th + i, NULL, &routine, NULL) != 0)
        {
            perror("Failed to create thread");
            return 1;
        }
        printf("Thread %d has started\n", i);
        i++;
    }
    i = 0;
    while (i < philo->num_of_philo)
    {
        if (pthread_join(th[i], NULL) != 0)
            return 2;
        printf("Thread %d has finished execution\n", i);
        i++;
    }
    pthread_mutex_destroy(&mutex);
    printf("Number of mails: %d\n", mails);
    return (0);
}

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

int error_message(t_info *philo, int error)
{
    if (error == 1)
        write(1, "Invalid input\n", 14);
    free(philo);
    return (-1);
}

int init_info_struct(t_info *info, char **argv, int argc)
{
    int i;
    i = 1;
    while (i < argc)
    {
        if (argv[i][0] == '-')
            return(-1);
        i++;
    }
    info->num_of_philo = ft_atoi(argv[1]);
    info->num_of_forks = info->num_of_philo;
    info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
	    info->num_of_meals = ft_atoi(argv[5]);
	info->forks = malloc(sizeof(int) * info->num_of_forks);
    i = 1;
    while(i < info->num_of_forks)
    {
        info->forks[i] = i;
        i++;
    }
	info->start_time = get_time();
    return(0);
}

// int init_philo_struct(t_info *philo, char **argv, int argc)
// {
//     philo->num_of_philo = ft_atoi(argv[1]);
//     philo->num_of_forks = philo->num_of_philo;
//     philo->time_to_die = ft_atoi(argv[2]);
// 	philo->time_to_eat = ft_atoi(argv[3]);
// 	philo->time_to_sleep = ft_atoi(argv[4]);
//     if (argc == 6)
// 	    philo->num_of_meals = ft_atoi(argv[5]);
//     return(0);
// }



int main(int argc, char **argv) 
{
    t_info *info;
    t_philo *philo;
    
    info = malloc(sizeof(t_info));
    philo = NULL;
    if ((argc != 5 && argc != 6) || init_info_struct(info, argv, argc) == -1)
        return(error_message(info, 1));
    // if (init_philo_struct(philo, argv, argc) == -1))
    //     return(error_message(philo, 1));
    if (create_threads_philo(info) == -1)
        return (-1);  
    free(philo); 
    return (0);
}