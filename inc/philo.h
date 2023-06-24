/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 08:47:47 by jyim              #+#    #+#             */
/*   Updated: 2023/03/21 10:24:06 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include "../inc/libft/libft.h"
# include "../inc/ft_printf/ft_printf.h"

/* State */
# define PICK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIEDED 4
# define ARGV_COUNT_ERROR "Philsopher argument: number_of_philospher \
time_to_die time_to_eat time_to_sleep [Number of meals]"
# define ARGV_DATA_ERROR "Wrong data, please input only positive numbers"

typedef struct s_table
{
	int				nos_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nos_eat;
	int				dieded;
	long long		start_time;
	int				all_eaten;
	struct s_philo	*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	printing;
	pthread_mutex_t	check;
	pthread_mutex_t	eaten;
	pthread_mutex_t	death;
}				t_table;

typedef struct s_philo
{
	int			id;
	long long	time_last_eat;
	int			times_eaten;
	int			left_fork_id;
	int			right_fork_id;
	t_table		*table;
	pthread_t	thread_id;
}				t_philo;

void		ft_error(const char *str);
long long	time_stamp(t_table *table);
void		launching(t_table *table);
void		print_status(t_philo *philo, int state);
void		smart_sleep(t_philo *philo, int state);
void		start_time(t_table *table);
int			init_data(t_table *table, int argc, char **argv);
void		*check_death(void *data);
int			isdead(t_table *table);
void		exit_launch(t_table *table);
void		*thread_routine(void *data);

#endif