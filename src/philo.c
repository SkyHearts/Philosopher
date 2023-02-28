/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:24:42 by jyim              #+#    #+#             */
/*   Updated: 2023/02/28 11:16:25 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table		table;

	if (argc == 5 || argc == 6)
	{

		// initialize forks/chopstick and philospher data;
		init_data(&table, argc, argv);
		// if ()
		launching(&table);
	}
	else
		 ;
	return (0);
}