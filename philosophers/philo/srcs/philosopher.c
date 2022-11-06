/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:29:10 by myoshika          #+#    #+#             */
/*   Updated: 2022/11/06 23:23:33 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo, t_info *i)
{
	
}

static void	think(t_philo *philo, t_info *i)
{
	
}

static void	sleep(t_philo *philo, t_info *i)
{
	
}

void	*life(void *p)
{
	t_philo	*philo;
	t_info	*i;

	philo = (t_philo *)p;
	i = (t_info *)i;
	while (1)
	{
		eat(p, i);
		think(p, i);
		sleep(p, i);
	}
	return (NULL);
}
