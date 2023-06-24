/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 08:47:41 by jyim              #+#    #+#             */
/*   Updated: 2023/03/21 11:32:40 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

static int	ft_atoi_num(const char *str)
{	
	size_t	i;
	size_t	sign;
	size_t	num;

	i = 0;
	sign = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	if (!ft_isdigit(str[i]) || str[i] == '\0')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num * sign);
}

/* Initialise forks and other mutex */
static void	init_mutex(t_table *table)
{
	int				i;
	pthread_mutex_t	*fork;
	int				n_fork;

	i = 0;
	n_fork = table->nos_philo;
	fork = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t) * n_fork);
	while (i < n_fork)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	table->fork = fork;
	pthread_mutex_init(&(table->printing), NULL);
	pthread_mutex_init(&(table->check), NULL);
	pthread_mutex_init(&(table->eaten), NULL);
	pthread_mutex_init(&(table->death), NULL);
}

/* Assign fork and initialise philos */
static void	init_philo(t_table *table)
{
	int		i;
	t_philo	*philo;
	int		n_philo;

	i = 0;
	n_philo = table->nos_philo;
	philo = (t_philo *) malloc (sizeof(t_philo) * n_philo);
	while (i < n_philo)
	{
		philo[i].id = i + 1;
		philo[i].times_eaten = 0;
		philo[i].left_fork_id = i;
		philo[i].right_fork_id = (i + 1) % n_philo;
		philo[i].table = table;
		i++;
	}
	table->philo = philo;
}

int	check_data(t_table *table)
{
	if (table->nos_philo == -1)
		return (1);
	if (table->time_to_die == -1)
		return (1);
	if (table->time_to_eat == -1)
		return (1);
	if (table->time_to_sleep == -1)
		return (1);
	return (0);
}

int	init_data(t_table *table, int argc, char **argv)
{
	start_time(table);
	table->nos_philo = ft_atoi_num(argv[1]);
	table->time_to_die = ft_atoi_num(argv[2]);
	table->time_to_eat = ft_atoi_num(argv[3]);
	table->time_to_sleep = ft_atoi_num(argv[4]);
	table->all_eaten = 0;
	table->nos_eat = -1;
	table->dieded = 0;
	if (argc == 6)
	{
		table->nos_eat = ft_atoi_num(argv[5]);
		if (table->nos_eat < 1)
			return (1);
	}
	if (check_data(table))
		return (1);
	init_mutex(table);
	init_philo(table);
	return (0);
}
