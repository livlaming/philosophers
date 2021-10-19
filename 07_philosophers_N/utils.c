/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/18 17:46:28 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/19 11:35:41 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int error_message(t_central *central, t_philo *philo, int error)
{
    if (error == 1)
        write(1, "Invalid input\n", 14);

    if (error == 2)
    {
        perror("Failed to create thread");
        write(1, "Failed to create thread\n", 24);
    }
    free(central); //uitgebreiden
    free(philo); //uitgebreiden
    return (-1);
}

unsigned long long  ft_atoull(const char *str)
{
    unsigned long long	result;
	long			sign;

	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		sign = sign * -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (result * 10 + *str - 48 > 9223372036854775807U && sign == 1)
			return (-1);
		if (result * 10 + *str - 48 > 9223372036854775808U)
			return (0);
		result = result * 10 + *str - 48;
		str++;
	}
    return ((unsigned long long)result * sign);
}

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	long				sign;

	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		sign = sign * -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (result * 10 + *str - 48 > 9223372036854775807U && sign == 1)
			return (-1);
		if (result * 10 + *str - 48 > 9223372036854775808U)
			return (0);
		result = result * 10 + *str - 48;
		str++;
	}
	return ((int)result * sign);
}