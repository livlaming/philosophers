/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/17 14:16:51 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/18 17:44:48 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdint.h>
#include <pthread.h>

#define DEAD 0
#define ALIVE 1

// 1 = number_of_philosophers
// 2 = time_to_die
// 3 = time_to_eat
// 4 = time_to_sleep
// 5 = [number_of_times_each_philosopher_must_eat]

typedef struct		s_central
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
    int             num_of_forks;
	pthread_mutex_t	*forks;
	pthread_mutex_t *eat;
	pthread_mutex_t *write;	
	pthread_mutex_t	*status;
	long			start_time;
    int				state;
	int				num_of_philo_full;
}					t_central;
 
typedef struct		s_philo
{
	long			ID;
	pthread_mutex_t *lfork;
	pthread_mutex_t *rfork;
	int				meals_left;
	long			last_eaten;
	pthread_mutex_t	director;
	t_central		*central;
}					t_philo;


#endif