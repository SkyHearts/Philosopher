/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 08:47:53 by jyim              #+#    #+#             */
/*   Updated: 2023/02/28 11:41:37 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

void	check_death(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	pthread_mutex_lock(&table->check);
	if (time_stamp(table) - philo->time_last_eat > table->time_to_die)
	{
		print_status(philo, DIEDED);
	}
	pthread_mutex_unlock(&table->check);
}

static void eat(t_philo *philo, t_table *table)
{	
	pthread_mutex_lock(&table->fork[philo->left_fork_id]);
	print_status(philo, PICK);
	pthread_mutex_lock(&table->fork[philo->right_fork_id]);
	print_status(philo, PICK);
	print_status(philo, EAT);
	smart_usleep(philo, EAT);
	pthread_mutex_lock(&table->check);
	philo->time_last_eat = time_stamp(table);
	philo->times_eaten += 1;
	pthread_mutex_unlock(&table->check);
	pthread_mutex_unlock(&table->fork[philo->left_fork_id]);
	pthread_mutex_unlock(&table->fork[philo->right_fork_id]);
}

static void ft_sleep(t_philo *philo, t_table *table)
{
	print_status(philo, SLEEP);
	smart_usleep(philo, SLEEP);
}

void	*thread_routine(void *data)
{
	t_philo		*philo;
	t_table		*table;

	philo = (t_philo *) data;
	table = philo->table;

	if (philo->id % 2 == 0)
		usleep(500);
	while (!(table->dieded))
	{
		eat(philo, table);
		if (philo->times_eaten == table->nos_eat)
			break ;
		ft_sleep(philo, table);
		print_status(philo, THINK);
		check_death(philo);
	}
	return (NULL);
}

void	launching(t_table *table)
{
	int i;
	int n_philo;
	t_philo *philo;
	
	i = 0;
	n_philo = table->nos_philo;
	philo = table->philo;
	while (i < n_philo)
	{
		pthread_create(&philo[i].thread_id, NULL, thread_routine, &philo[i]);	
		i++;
	}
	i = 0;
	while (i < n_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < n_philo)
	{
		pthread_mutex_destroy(table->fork);
		i++;
	}
	pthread_mutex_destroy(&table->printing);
}