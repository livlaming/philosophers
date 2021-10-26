/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_and_sleep.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 11:18:20 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/26 13:20:17 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>
#include <unistd.h>

uint64_t	get_time_mseconds(void)
{
	struct timeval	tv;
	unsigned long	time_in_mill;

	time_in_mill = 0;
	gettimeofday(&tv, NULL);
	time_in_mill = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_mill);
}

static unsigned long	get_time_useconds(void)
{
	struct timeval	tv;
	unsigned long	time_in_useconds;

	time_in_useconds = 0;
	gettimeofday(&tv, NULL);
	time_in_useconds = (tv.tv_sec * 1000000) + tv.tv_usec;
	return (time_in_useconds);
}

void	stupid_sleep(uint64_t ms)
{
	unsigned long	entry;

	entry = get_time_useconds();
	ms *= 1000;
	while ((get_time_useconds() - entry) < ms)
		usleep(100);
}
