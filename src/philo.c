/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:24:42 by jyim              #+#    #+#             */
/*   Updated: 2023/03/25 18:07:13 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table		table;

	if (argc == 5 || argc == 6)
	{
		if (init_data(&table, argc, argv))
		{
			ft_error(ARGV_DATA_ERROR);
			return (1);
		}
		launching(&table);
		exit_launch(&table);
		//system("leaks -q philo");
	}
	else
		ft_error(ARGV_COUNT_ERROR);
	return (0);
}
