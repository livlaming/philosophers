/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/18 17:46:28 by livlamin      #+#    #+#                 */
/*   Updated: 2021/11/05 10:00:05 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	error_message(t_central *central, t_philo *philo, int error)
{
	if (error == 1)
	{
		write(1, "Invalid input\n", 14);
		free(central);
		return (-1);
	}
	if (error == 2)
		write(1, "Failed to create thread\n", 24);
	if (error == 3)
		write(1, "Failed to join thread\n", 24);
	if (error == 4)
		write(1, "Malloc failed\n", 14);
	if (error != 4)
		unlock_and_destroy(philo, central);
	else
		free(central);
	return (-1);
}

void	*error_message_2(int error)
{
	if (error == 1)
		write(1, "Failed to create thread\n", 24);
	if (error == 2)
		write(1, "Failed to join thread\n", 24);
	return ((void *) NULL);
}

int	ft_atoi(const char *str)
{
	uint64_t	result;
	long		sign;

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

void	write_state(char *str, t_philo *philo, long ID)
{
	pthread_mutex_lock(philo->central->write);
	if (check_status(philo) == ALIVE)
	{
		printf("%lld %zu %s\n",
			get_time_mseconds() - philo->central->start_time, ID, str);
	}
	pthread_mutex_unlock(philo->central->write);
}

uint64_t	ft_strtoull(const char *str)
{
	uint64_t	nbr;

	nbr = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if ((nbr == 1844674407370955161 && (*str) > '5')
			|| (nbr > 1844674407370955161))
			return (-1);
		nbr = (nbr * 10) + (*str - '0');
		str++;
	}
	return (nbr);
}
