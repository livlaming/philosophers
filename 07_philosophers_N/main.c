/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 10:50:25 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/19 11:54:44 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

int check_input(int argc, char **argv)
{
    int i;

    i = 1;
    while (i < argc)
    {
        if (argv[i][0] < '0' || argv[i][0] > '9')
            return (-1);
        i++;
    }
    return (0);
}

int main(int argc, char **argv)
{
    t_central *central;
    t_philo *philo;

    philo = NULL;
    central = malloc(sizeof(t_central));
    if (!central)
        return (-1);
    if ((argc != 5 && argc != 6) || check_input(argc, argv) == -1)
        return(error_message(central, philo, 1));
    if (init_central_struct(central, argv, argc) == -1)
        return(error_message(central, philo, 1));
    philo = malloc(sizeof(t_philo) * central->num_of_philo);
    if (!philo)
        return (-1);
    if (init_philo_struct(central, philo) == -1)
        return(error_message(central, philo, 1));
    
    return (0);
}