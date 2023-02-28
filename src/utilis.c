/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:29:30 by jyim              #+#    #+#             */
/*   Updated: 2023/02/28 11:33:12 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void start_time(t_table *table)
{
	struct timeval start_time;

	gettimeofday(&start_time, NULL);
	long long ms_start =
		(long long)(start_time.tv_sec) * 1000 +
		(long long)(start_time.tv_usec) / 1000;
	table->start_time =  ms_start;
}

long long time_stamp(t_table *table)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	long long ms_since_start =
		((long long)(current_time.tv_sec) * 1000 +
		(long long)(current_time.tv_usec) / 1000) -
		(table->start_time);
    return (ms_since_start);
}

void smart_usleep(t_philo *philo, int state)
{
	t_table *table;
	long long current_time;
	long long delay;
	
	table = philo->table;
	if (state == EAT)
		delay = table->time_to_eat;
	else if (state == SLEEP)
		delay = table->time_to_sleep;
	else
		delay = 0;
	current_time = time_stamp(table);
	while (time_stamp(table) - current_time <= delay)
		usleep (50);
}

void	print_status(t_philo *philo, int state)
{
	int id;
	t_table *table;

	table = philo->table;
	pthread_mutex_lock(&table->printing);
	id = philo->id;
	if (state == PICK)
		printf("%lld %d has taken a fork\n", time_stamp(philo->table), id);
	else if (state == EAT)
		printf("%lld %d is eating\n", time_stamp(philo->table), id);
	else if (state == SLEEP)
		printf("%lld %d is sleeping\n", time_stamp(philo->table), id);
	else if (state == THINK)
		printf("%lld %d is thinking\n", time_stamp(philo->table), id);
	else if (state == DIEDED)
	{
		printf("%lld %d died\n", time_stamp(philo->table), id);
		exit(0);
	}
	pthread_mutex_unlock(&table->printing);
}