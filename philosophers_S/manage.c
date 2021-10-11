/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manage.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 09:48:33 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/11 11:28:51 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>

void* manage(void *arg)
{
    t_philo *philo;

    philo = arg;
    while(1)
    {
        philo->time_left -= (get_time(philo->info->start_time) - philo->last_eaten);
        if (philo->time_left <= 0 && philo->state == ALIVE)
        {
            philo->state = DEAD;
            write_state("died", philo, philo->ID);
            return (philo);
        }
        if (philo->info->num_of_philo_full == philo->info->num_of_philo)
        {
            write_state("All philosophers are full", NULL, 0);
            return (philo);
        }
    }
    return (philo);
}


// void* manage(void *arg)
// {
//     t_philo *philo;
//     int ID;

//     philo = arg;
//     ID = 0;
//     while(1)
//     {
//         while (ID < philo->info->num_of_philo)
//         {
//             get_time(philo[ID].time_left);
//             if (philo[ID].time_left <= 0 && philo[ID].state == ALIVE)
//             {
//                 philo[ID].state = DEAD;
//                 write_state("died", philo, ID);
//                 return (philo);
//             }
//             if (philo->info->num_of_philo_full == philo->info->num_of_philo)
//             {
//                 write_state("All philosophers are full", NULL, 0);
//                 return (philo);
//             }
//             ID++;
//         }
//         ID = 0;
//     }
//     return (philo);
// }