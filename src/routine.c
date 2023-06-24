/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 08:47:53 by jyim              #+#    #+#             */
/*   Updated: 2023/03/22 10:54:43 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

int	check_num_eat(t_philo *philo, t_table *table)
{
	int		i;
	(void) philo;
	i = 0;
	while (table->nos_eat != -1 && i < table->nos_philo
		&& table->philo[i].times_eaten >= table->nos_eat)
		i++;
	if (i == table->nos_philo)
	{
		table->all_eaten = 1;
		pthread_mutex_unlock(&(table->eaten));
		// pthread_mutex_unlock(&(table->check));
		return (1);
	}
	return (0);
}

void	*check_death(void *data)
{
	int		i;
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *) data;
	table = philo->table;
	while (isdead(table))
	{
		i = 0;
		// pthread_mutex_lock(&(table->check));
		pthread_mutex_lock(&(table->eaten));
		if (time_stamp(table) - philo->time_last_eat > table->time_to_die)
		{
			pthread_mutex_unlock(&(table->eaten));
			print_status(philo, DIEDED);
			pthread_mutex_lock(&(table->death));
			table->dieded = 1;
			pthread_mutex_unlock(&(table->death));
		}
		if (check_num_eat(philo, table))
			return (NULL);
		pthread_mutex_unlock(&(table->eaten));
		usleep(25);
		// pthread_mutex_unlock(&(table->check));
	}
	return (NULL);
}

int	eat(t_philo *philo, t_table *table)
{	
	if (isdead(table))
	{
		pthread_mutex_lock(&(table->fork[philo->left_fork_id]));
		print_status(philo, PICK);
		if (table->nos_philo == 1)
			return (1);
		pthread_mutex_lock(&(table->fork[philo->right_fork_id]));
		print_status(philo, PICK);
		print_status(philo, EAT);
		pthread_mutex_lock(&(table->eaten));
		philo->time_last_eat = time_stamp(table);
		philo->times_eaten++;
		pthread_mutex_unlock(&(table->eaten));
		smart_sleep(philo, EAT);
		pthread_mutex_unlock(&(table->fork[philo->left_fork_id]));
		pthread_mutex_unlock(&(table->fork[philo->right_fork_id]));
		usleep(25);
	}
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	t_table		*table;

	table = philo->table;
	if (isdead(table))
	{
		print_status(philo, SLEEP);
		smart_sleep(philo, SLEEP);
		print_status(philo, THINK);
		usleep(25);
		return (0);
	}
	return (1);
}

void	*thread_routine(void *data)
{
	t_philo		*philo;
	t_table		*table;
	pthread_t	death_thread;

	philo = (t_philo *) data;
	table = philo->table;
	if (!(philo->id % 2))
		smart_sleep(philo, 0);
	pthread_create(&(death_thread), NULL, check_death, philo);
	pthread_detach(death_thread);
	while (isdead(table))
	{
		if (eat(philo, table))
		{
			smart_sleep(philo, DIEDED);
			return (NULL);
		}
		if (ft_sleep(philo))
			return (NULL);
	}
	return (NULL);
}
