/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:29:10 by myoshika          #+#    #+#             */
/*   Updated: 2022/11/10 16:31:28 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	monitor(t_philo *p, t_info *i)
{
	pthread_mutex_lock(&i->monitor);
	if (p->id == i->num_of_philosophers)
		if (p->meals_eaten == i->meals_to_eat)
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

static bool	eating(t_philo *p, t_info *i)
{
	if (!monitor(p, i))
		return (false);
	pthread_mutex_lock(&i->forks[p->left_fork]);
	print_action(p, i, FORK_MSG);
	if (!monitor(p, i))
	{
		pthread_mutex_unlock(&i->forks[p->left_fork]);
		return (false);
	}
	pthread_mutex_lock(&i->forks[p->right_fork]);
	pthread_mutex_lock(&i->print);
	printf("%ld %d %s\n", timestamp(p), p->id, FORK_MSG);
	printf("%ld %d %s\n", timestamp(p), p->id, EAT_MSG);
	pthread_mutex_unlock(&i->print);
	p->time_of_last_meal = timestamp(p);
	//precise_sleep(timestamp(p) + i->time_to_eat, p);
	usleep(1000 * i->time_to_eat);
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
	//precise_sleep(timestamp(p) + i->time_to_sleep, p);
	usleep(1000 * i->time_to_sleep);
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
	philo->start_time = time_in_ms();
	philo->time_of_last_meal = philo->start_time;
	if (philo->id % 2 == 0)
		thinking(p, i);
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
