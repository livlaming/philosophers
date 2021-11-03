/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_state.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 11:16:43 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/11 11:40:21 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

void    write_state(char *str, t_philo *philo, size_t ID)
{
    pthread_mutex_lock(philo->write);
    if (philo == NULL)
       printf("%s\n", str);
    else
        printf("%d %zu %s\n", get_time(philo->info->start_time), ID, str);
    pthread_mutex_unlock(philo->write);
}