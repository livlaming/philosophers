/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/17 14:16:51 by livlamin      #+#    #+#                 */
/*   Updated: 2021/11/03 11:51:19 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdint.h>
# include <pthread.h>

# define DEAD 0
# define ALIVE 1

/* 
** 1st argument = number_of_philosophers
** 2nd argument = time_to_die
** 3rd argument = time_to_eat
** 4th argument = time_to_sleep
** 5th argument = [number_of_times_each_philosopher_must_eat]
*/

/* 
** central struct is used to:
** - store central information
** forks
** eat_lock
** write_lock
** state == 0 -> no philos_dead
** state == 1 -> one philo_dead
*/

/* 
** philo_struct = made for every philosopher
** philo_struct points to central information
*/

// typedef struct s_central
// {
// 	int					num_of_philo;
// 	uint64_t			time_to_die;
// 	uint64_t			time_to_eat;
// 	uint64_t			time_to_sleep;
// 	int					num_of_meals;
// 	int					num_of_forks;
// 	pthread_mutex_t		*forks;
// 	pthread_mutex_t		*eat;
// 	pthread_mutex_t		*write;	
// 	pthread_mutex_t		*status;
// 	pthread_mutex_t		*full;
// 	uint64_t			start_time;
// 	int					state;
// 	int					num_of_philo_full;
// }						t_central;

// typedef struct s_philo
// {
// 	int					ID;
// 	pthread_mutex_t		*lfork;
// 	pthread_mutex_t		*rfork;
// 	int					meals_left;
// 	uint64_t			last_eaten;
// 	t_central			*central;
// }						t_philo;


#endif