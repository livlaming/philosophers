/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/17 14:16:51 by livlamin      #+#    #+#                 */
/*   Updated: 2021/08/19 11:33:13 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdint.h>
#include <pthread.h>

// number_of_philosophers
// time_to_die
// time_to_eat
// time_to_sleep
// [number_of_times_each_philosopher_must_eat]

typedef struct		s_info
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep; 
	int				num_of_meals;
    int             num_of_forks;
	int				*forks;
	int				start_time;
}					t_info;

typedef struct		s_philo
{
	int				ID;
	pthread_mutex_t *lfork;
	pthread_mutex_t *rfork;
	uint64_t		start_time;
	t_info			*info;
}					t_philo;

uint64_t    ft_atou(const char *str);
int         ft_atoi(const char *str);

#endif