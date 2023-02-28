/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 08:47:41 by jyim              #+#    #+#             */
/*   Updated: 2023/02/28 11:32:02 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

static void init_fork(t_table *table)
{
	int i;
	pthread_mutex_t *fork;
	int n_fork;

	i = 0;
	
	n_fork = table->nos_philo;
	fork = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t) * n_fork);
	while (i < n_fork)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	table->fork = fork;
}

static void init_philo(t_table *table)
{
	int i;
	t_philo *philo;
	int n_philo;

	i = 0;
	n_philo = table->nos_philo;
	philo = (t_philo *) malloc (sizeof(t_philo) * n_philo);
	while (i < n_philo)
	{
		philo[i].id = i + 1;
		philo[i].times_eaten = 0;
		philo[i].time_last_eat = time_stamp(table);
		philo[i].left_fork_id = i;
		philo[i].right_fork_id = (i + 1) % n_philo;
		philo[i].table = table;
		i++;
	}
	table->philo = philo;
}

void	init_data(t_table *table, int argc, char **argv)
{
	
	start_time(table);
	table->nos_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->nos_eat = 0;
	table->dieded = 0;
	if (argc == 6)
		table->nos_eat = ft_atoi(argv[5]);
	pthread_mutex_init(&table->printing, NULL);
	pthread_mutex_init(&table->check, NULL);
	init_fork(table);
	init_philo(table);
}