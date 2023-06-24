/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:09:31 by jyim              #+#    #+#             */
/*   Updated: 2023/03/21 11:32:42 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_launch(t_table *table)
{
	int		i;
	int		n_philo;
	t_philo	*philo;

	i = 0;
	n_philo = table->nos_philo;
	philo = table->philo;
	i = 0;
	while (i < n_philo)
	{
		pthread_mutex_destroy(&(table->fork[i]));
		i++;
	}
	free(table->fork);
	free(table->philo);
	pthread_mutex_destroy(&table->printing);
	pthread_mutex_destroy(&table->check);
	pthread_mutex_destroy(&table->eaten);
	pthread_mutex_destroy(&table->death);
}

void	launching(t_table *table)
{
	int		i;
	int		n_philo;
	t_philo	*philo;

	i = 0;
	n_philo = table->nos_philo;
	philo = table->philo;
	while (i < n_philo)
	{
		philo[i].time_last_eat = time_stamp(table);
		pthread_create(&(philo[i].thread_id), NULL, thread_routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < n_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
}
