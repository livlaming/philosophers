/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   old_main.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/16 13:27:05 by livlamin      #+#    #+#                 */
/*   Updated: 2021/08/19 11:34:48 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

int mails = 0;
pthread_mutex_t mutex;

void* routine() {
    // for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        mails++;
        struct timeval  tv;
        gettimeofday(&tv, NULL);
        uint64_t time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ; // sec to millisec
        printf("%lld X has taken a fork\n", time_in_mill);
        printf("%lld X is eating\n", time_in_mill);
        printf("%lld X is sleeping\n", time_in_mill);
        printf("%lld X died\n", time_in_mill);
        pthread_mutex_unlock(&mutex);
    return(NULL);
}
#include <stdio.h>
int create_threads_philo(t_info *philo)
{
    pthread_t *th;
    int i;
    int *forks;

    i = 1;
    th = malloc(sizeof(pthread_t) * philo->no_philo);
    forks = malloc(sizeof(char) * philo->no_forks);
    while(i < philo->no_forks)
    {
        forks[i] = i;
        i++;
    }
    i = 0;
    pthread_mutex_init(&mutex, NULL);
    while (i < philo->no_philo)
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
    while (i < philo->no_philo)
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



// ◦ timestamp_in_ms X has taken a fork ◦ timestamp_in_ms X is eating
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

int init_struct(t_info *philo, char **argv, int argc)
{
    int i;
    i = 1;
    while (i < argc)
    {
        if (argv[i][0] == '-')
            return(-1);
        i++;
    }
    philo->no_philo = ft_atoi(argv[1]);
    philo->no_forks = philo->no_philo;
    philo->tt_die = ft_atou(argv[2]);
	philo->tt_eat = ft_atou(argv[3]);
	philo->tt_sleep = ft_atou(argv[4]);
    if (argc == 6)
	    philo->no_meals = ft_atoi(argv[5]);
    return(0);
}
int main(int argc, char **argv) 
{
    t_info *philo;
    
    philo = malloc(sizeof(t_info));
    if (argc != 5 && argc != 6)
        return(error_message(philo, 1));
    if (init_struct(philo, argv, argc) == -1)
        return(error_message(philo, 1));
    if (create_threads_philo(philo) == -1)
        return (-1);  
    free(philo); 
    // system("leaks philosophers");
    return (0);
}