/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/17 14:16:51 by livlamin      #+#    #+#                 */
/*   Updated: 2021/10/11 12:04:32 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdint.h>
#include <pthread.h>

#define DEAD 0
#define ALIVE 1

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
	pthread_mutex_t	*forks;
	pthread_mutex_t *eat; //
	int				start_time;
	int				num_of_philo_full;
}					t_info;

typedef struct		s_philo
{
	long				ID;
	pthread_mutex_t *lfork;
	pthread_mutex_t *rfork;
	pthread_mutex_t *write;
	int				meals_left;
	int				time_left;
	int				last_eaten;
	int				state;
	pthread_mutex_t	manage;
	t_info			*info;
}					t_philo;

int     		print_cur_info_struct(t_info *info); //
int     		print_cur_philo_struct(t_philo *philo); //
int				ft_atoi(const char *str);
uint64_t		ft_atou(const char *str);
int				init_philo_struct(t_info *info, t_philo *philo);
int				init_info_struct(t_info *info, char **argv, int argc);
int     		get_time(int start_time);
unsigned long	get_time_useconds(void);
void			stupid_sleep(unsigned long ms);
void*			routine_left_right(void *arg);
void*			routine_right_left(void *arg);
void*			manage(void *arg);
void			write_state(char *str, t_philo *philo, size_t ID);
void   			eating(t_philo *philo);

#endif