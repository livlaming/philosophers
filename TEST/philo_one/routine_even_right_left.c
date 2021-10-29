/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_even_right_left.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 12:58:27 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/29 13:54:25 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine_even_right_left(void *arg)
{
	t_philo		*philo;
	pthread_t	director;

	philo = arg;
	director = NULL;
	
	philo->last_eaten = get_time_mseconds();
	if (pthread_create(&director, NULL, &direct, philo) != 0)
		return ((void *) NULL); // error?
	while (check_status(philo) == 1)
	{
		pthread_mutex_lock(philo->rfork);
		write_state("has taken a fork", philo, philo->ID);
		pthread_mutex_lock(philo->lfork);
		write_state("has taken a fork", philo, philo->ID);
		eating_right_left(philo);
		write_state("is sleeping", philo, philo->ID);
		stupid_sleep(philo->central->time_to_sleep);
		write_state("is thinking", philo, philo->ID);
	}
	if (pthread_join(director, NULL) != 0)
		return ((void *) NULL); // error?
	return ((void *) NULL);
}
