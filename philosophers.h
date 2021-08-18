/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/17 14:16:51 by livlamin      #+#    #+#                 */
/*   Updated: 2021/08/17 15:23:27 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdint.h>

// number_of_philosophers
// time_to_die
// time_to_eat
// time_to_sleep
// [number_of_times_each_philosopher_must_eat]

typedef struct		s_info
{
	int				no_philo;
	uint64_t		tt_die;
	uint64_t		tt_eat;
	uint64_t		tt_sleep; 
	int				no_meals;
    int             no_forks;
	// sem_t			*fork_sema;
	// sem_t			*write_sema;
	// sem_t			*eat_sema;
	// t_state			state;
	// uint64_t		start_time;
}					t_info;

uint64_t    ft_atou(const char *str);
int         ft_atoi(const char *str);

#endif