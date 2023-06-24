/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:29:30 by jyim              #+#    #+#             */
/*   Updated: 2023/03/21 12:02:56 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	isdead(t_table *table)
{
	pthread_mutex_lock(&(table->death));
	pthread_mutex_lock(&(table->eaten));
	if (table->dieded == 1 || table->all_eaten)
	{
		pthread_mutex_unlock(&(table->death));
		pthread_mutex_unlock(&(table->eaten));
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&(table->death));
		pthread_mutex_unlock(&(table->eaten));
		return (1);
	}
}

void	start_time(t_table *table)
{
	struct timeval	start_time;
	long long		ms_start;

	gettimeofday(&start_time, NULL);
	ms_start = (long long)start_time.tv_sec * 1000
		+ (long long)start_time.tv_usec / 1000;
	table->start_time = ms_start;
}

long long	time_stamp(t_table *table)
{
	struct timeval	current_time;
	long long		ms_since_start;

	gettimeofday(&current_time, NULL);
	ms_since_start = ((long long)current_time.tv_sec * 1000
			+ (long long)current_time.tv_usec / 1000) - (table->start_time);
	return (ms_since_start);
}

void	smart_sleep(t_philo *philo, int state)
{
	t_table		*table;
	long long	current_time;
	long long	delay;

	table = philo->table;
	if (state == EAT)
		delay = table->time_to_eat;
	else if (state == SLEEP)
		delay = table->time_to_sleep;
	else if (state == DIEDED)
		delay = table->time_to_die + 1;
	else
		delay = table->time_to_eat / 10;
	current_time = time_stamp(table);
	while (time_stamp(table) - current_time < delay)
		usleep(delay / 10);
}

void	print_status(t_philo *philo, int state)
{
	int		id;
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->printing);
	if (isdead(table))
	{
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
			printf("%lld %d died\n", time_stamp(philo->table), id);
		pthread_mutex_unlock(&table->printing);
	}
	else
		pthread_mutex_unlock(&table->printing);
}
