/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:29:10 by myoshika          #+#    #+#             */
/*   Updated: 2022/11/08 23:46:19 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	monitor(t_philo *p, t_info *i)
{
	if (p->id == i->num_of_philosophers)
		if (p->meals_eaten == i->meals_to_eat)
			i->should_exit = true;
	if (i->should_exit)
		return (false);
	if (timestamp(i) - p->time_of_last_meal > i->time_to_die) // >= or >？
	{
		print_action(p, i, DIE_MSG);
		return (false);
	}
	return (true);
}

static bool	eating(t_philo *p, t_info *i)
{
	if (!monitor(p, i))
		return (false);
	pthread_mutex_lock(&i->forks[p->left_fork]);
	printf("[id:%d]", p->id);
	fflush(stdout);
	print_action(p, i, FORK_MSG);
	if (!monitor(p, i))
	{
		pthread_mutex_unlock(&i->forks[p->left_fork]);
		return (false);
	}
	pthread_mutex_lock(&i->forks[p->right_fork]);
	print_action(p, i, FORK_MSG);
	p->time_of_last_meal = timestamp(i);
	print_action(p, i, EAT_MSG);
	usleep(i->time_to_eat);
	p->meals_eaten++;
	pthread_mutex_unlock(&i->forks[p->left_fork]);
	pthread_mutex_unlock(&i->forks[p->right_fork]);
	return (true);
}

static bool	sleeping(t_philo *p, t_info *i)
{
	if (!monitor(p, i))
		return (false);
	print_action(p, i, SLEEP_MSG);
	usleep(i->time_to_sleep);
	return (true);
}

static bool	thinking(t_philo *p, t_info *i)
{
	if (!monitor(p, i))
		return (false);
	print_action(p, i, THINK_MSG);
	return (true);
}

void	*life(void *p)
{
	t_philo	*philo;
	t_info	*i;

	philo = (t_philo *)p;
	i = (t_info *)philo->i;
	while (1)
	{
		if (!eating(p, i))
			break ;
		if (!sleeping(p, i))
			break ;
		if (!thinking(p, i))
			break ;
	}
	return (NULL);
}
