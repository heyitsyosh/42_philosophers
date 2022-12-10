/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:48:58 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/10 11:58:31 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitor(void *p)
{
	t_philo	*philo;
	t_info	*i;

	philo = (t_philo *)p;
	i = (t_info *)philo->i;
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
