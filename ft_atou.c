/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atou.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/17 14:57:24 by livlamin      #+#    #+#                 */
/*   Updated: 2021/08/19 10:54:59 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint64_t  ft_atou(const char *str)
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
    return ((uint64_t)result * sign);
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