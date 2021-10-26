/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/17 14:16:51 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/26 11:29:03 by livlamin      ########   odam.nl         */
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
	int					num_of_philo;
	uint64_t			time_to_die;
	uint64_t			time_to_eat;
	uint64_t			time_to_sleep;
	int					num_of_meals;
    int             	num_of_forks;
	pthread_mutex_t		*forks;
	pthread_mutex_t 	*eat;
	pthread_mutex_t 	*write;	
	pthread_mutex_t		*status;
	uint64_t			start_time;
    int					state;
	int					num_of_philo_full;
}						t_central;
 
typedef struct		s_philo
{
	long				ID;
	pthread_mutex_t 	*lfork;
	pthread_mutex_t 	*rfork;
	int					meals_left;
	uint64_t			last_eaten;
	t_central			*central;
}						t_philo;

int 				error_message(t_central *central, t_philo *philo, int error);
int					ft_atoi(const char *str);
uint64_t    		ft_strtoull(const char *str);
uint64_t			get_time_mseconds(void);
int					init_central_struct(t_central *central, char **argv, int argc);
int					init_philo_struct(t_central *central, t_philo *philo);
void    			stupid_sleep(uint64_t ms);
void    			write_state(char *str, t_philo *philo, long ID);
void*				routine_odd_left_right(void *arg);
void*				routine_even_right_left(void *arg);
void				eating(t_philo *philo);
void				*direct(void *arg);
void				unlock_and_destroy(t_philo *philo, t_central *central);
void    			destroy_mutex(t_philo *philo);
void				unlock_forks(t_philo *philo);	

//REMOVE BELOW!
int     print_cur_central_struct(t_central *central);
int     print_cur_philo_struct(t_philo *philo);	
#endif