/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_state.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 13:10:14 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/12 09:53:41 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

void    write_state(char *str, t_philo *philo, long ID)
{
    if (philo->state == 1)
    {
        pthread_mutex_lock(philo->info->write);
        if (!philo)
            printf("%s\n", str);
        else
            printf("%d %zu %s\n", get_time(philo->info->start_time), ID, str);
        pthread_mutex_unlock(philo->info->write);
    }
    // else
    //     printf("%d %zu died\n", get_time(philo->info->start_time), ID);
}