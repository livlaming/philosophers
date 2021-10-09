
Skip to content
Pull requests
Issues
Marketplace
Explore
@livlaming
livlaming /
philosophers

1
0

    0

Code
Issues
Pull requests
Actions
Projects
Wiki
Security
Insights

More
philosophers/main.c
Cannot retrieve latest commit at this time.
0 contributors
238 lines (209 sloc) 6.63 KB
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/16 13:27:05 by livlamin      #+#    #+#                 */
/*   Updated: 2021/08/23 18:05:02 by livlamin      ########   odam.nl         */
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

int error_message(t_info *info, t_philo *philo, int error)
{
    if (error == 1)
        write(1, "Invalid input\n", 14);

    if (error == 2)
    {
        perror("Failed to create thread");
        write(1, "Failed to create thread\n", 24);
    }
    // free(philo->forks);?
    //check for mallocs, 
    free(info);
    free(philo);
    return (-1);
}

int     get_time(int start_time)
{
    struct timeval  tv;
    int time_in_mill;

    time_in_mill = 0;
    gettimeofday(&tv, NULL);
    time_in_mill = (tv.tv_sec * 1000) + (tv.tv_usec / 1000); // sec to millisec
    return (time_in_mill - start_time);
}

unsigned long     get_time_useconds(void)
{
    struct timeval  tv;
    unsigned long time_in_useconds;

    time_in_useconds = 0;
    gettimeofday(&tv, NULL);
    time_in_useconds = (tv.tv_sec * 1000000) + tv.tv_usec; // sec to microsec
    return (time_in_useconds);
}

void    stupid_sleep(unsigned long ms)
{
    unsigned long    entry;

    entry = get_time_useconds();
    ms *= 1000;
    while ((get_time_useconds() - entry) < ms)
        usleep(100);
}

void* routine_left_right(void *arg) 
{
    t_philo *philo;

    philo = arg;
    pthread_mutex_lock(philo->lfork);
    printf("%d %d has taken a fork\n", get_time(philo->info->start_time), philo->ID);
    pthread_mutex_lock(philo->rfork);
    printf("%d %d has taken a fork\n", get_time(philo->info->start_time), philo->ID);
    printf("%d %d is eating\n", get_time(philo->info->start_time), philo->ID);
    stupid_sleep(philo->info->time_to_eat);
    // usleep(10);
    printf("%d %d is sleeping\n", get_time(philo->info->start_time), philo->ID);
    pthread_mutex_unlock(philo->lfork);
    pthread_mutex_unlock(philo->rfork);
    // printf("%d %d is died\n", get_time(philo->info->start_time), philo->ID);
    return(NULL);
}

void* routine_right_left(void *arg) 
{
    t_philo *philo;

    philo = arg;
    pthread_mutex_lock(philo->rfork);
    printf("%d %d has taken a fork\n", get_time(philo->info->start_time), philo->ID);
    pthread_mutex_lock(philo->lfork);
    printf("%d %d has taken a fork\n", get_time(philo->info->start_time), philo->ID);
    printf("%d %d is eating\n", get_time(philo->info->start_time), philo->ID);
    stupid_sleep(philo->info->time_to_eat);
    printf("%d %d is sleeping\n", get_time(philo->info->start_time), philo->ID);
    pthread_mutex_unlock(philo->rfork);
    pthread_mutex_unlock(philo->lfork);
    // printf("%d %d is died\n", get_time(philo->info->start_time), philo->ID);
    return(NULL);
}


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
	    philo[ID].state = ALIVE;
	    philo[ID].info = info;
        print_cur_philo_struct(&philo[ID]);
        ID++;
    }
    return (0);
}

int create_threads(t_info *info, t_philo *philo, int i)
{
    pthread_t *thread;

    thread = malloc(sizeof(pthread_t) * info->num_of_philo);
    // pthread_mutex_init(&mutex, NULL);
    while (i < info->num_of_philo)
    {
        if (i & 1) //odd
        {
            if (pthread_create(&thread[i], NULL, &routine_right_left, &philo[i]) != 0)
                return(error_message(info, philo, 2));
        }
        else
        {
            if (pthread_create(&thread[i], NULL, &routine_left_right, &philo[i]) != 0)
                return(error_message(info, philo, 2));
        }
        printf("Thread %d has started\n", i); //
        i++;
    }
    i = 0;
    while (i < info->num_of_philo)
    {
        if (pthread_join(thread[i], NULL) != 0)
            return 2;
        printf("Thread %d has finished execution\n", i); //
        i++;
    }
    // pthread_mutex_destroy(&mutex);
    return (0);
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
	info->start_time = get_time(0);
    return(0);
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
    free(philo); 
    free(info);
    return (0);
}