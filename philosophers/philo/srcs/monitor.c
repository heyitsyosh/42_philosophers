/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:48:58 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/08 05:32:23 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitor(void *info)
{
	t_philo	*philos;
	t_info	*i;

	i = (t_info *)info;
	philos = (t_philo *)i->philos;
	pthread_mutex_lock(&i->monitor);
	if (philo->id == i->num_of_philosophers)
		if (philo->meals_eaten == i->meals_to_eat)
			i->should_exit = true;
	if (i->should_exit)
	{
		pthread_mutex_unlock(&i->monitor);
		return (false);
	}
	if (timestamp(p) - p->time_of_last_meal >= i->time_to_die)
	{
		print_action(p, i, DIE_MSG);
		i->should_exit = true;
		pthread_mutex_unlock(&i->monitor);
		return (false);
	}
	pthread_mutex_unlock(&i->monitor);
	return (true);
}

bool	make_monitor(t_info *i)
{
	if (pthread_create(&(i->monitor_tid), NULL, life, i) != 0)
	{
		printf("failed to create thread\n");
		return (false);
	}
	return (true);
}
