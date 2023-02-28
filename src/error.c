/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:15:11 by jyim              #+#    #+#             */
/*   Updated: 2023/02/22 11:18:23 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_writestr(char *str)
{
	write(2, &str, ft_strlen(str));
	write(2, "\n", 1);
}

void	ft_error(char *str)
{
	ft_writestr(str);
	exit(1);
}
