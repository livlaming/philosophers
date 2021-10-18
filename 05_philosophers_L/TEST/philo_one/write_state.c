/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_state.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 13:10:14 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/18 17:28:35 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

void    write_state(char *str, t_philo *philo, long ID)
{
    pthread_mutex_lock(philo->info->write);
    if (philo->info->state == 1)
    {
        if (!philo)
            printf("%s\n", str);
        else
            printf("%ld %zu %s\n", get_time(philo->info->start_time), ID, str);
        
    }
    else
    {
            printf("died");
    }
    pthread_mutex_unlock(philo->info->write);
    // else
    //     printf("%d %zu died\n", get_time(philo->info->start_time), ID);
}