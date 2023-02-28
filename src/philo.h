/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 08:47:47 by jyim              #+#    #+#             */
/*   Updated: 2023/02/28 11:15:50 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include "../inc/libft/libft.h"

/* State */
# define PICK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIEDED 4

typedef struct 			s_philo {
	int 		id;
	long long 	time_last_eat;
	int 		times_eaten;
	int 		left_fork_id;
	int 		right_fork_id;
	struct s_table	*table;
	pthread_t 	thread_id;
}				t_philo;				

typedef struct s_table
{
	int			nos_philo;
	int 		time_to_die;
	int 		time_to_eat;
	int 		time_to_sleep;
	int 		nos_eat;
	int			dieded;
	long long start_time;
	t_philo		*philo;
	pthread_mutex_t *fork; 
	pthread_mutex_t printing;
	pthread_mutex_t check; 
}				t_table;

void	ft_error(char *str);
long long time_stamp(t_table *table);
void	launching(t_table *table);
void	print_status(t_philo *philo, int state);
void smart_usleep(t_philo *philo, int state);
void start_time(t_table *table);
void	init_data(t_table *table, int argc, char **argv);
void	check_death(t_philo *philo);

#endif