/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:29:10 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/15 19:08:31 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>
#include <unistd.h>

static bool	taking_forks(t_philo *p, t_info *i)
{
	pthread_mutex_lock(&i->forks[p->left_fork]);
	if (!print_action(timestamp_in_ms(p), p, i, FORK_MSG))
	{
		pthread_mutex_unlock(&i->forks[p->left_fork]);
		return (false);
	}
	pthread_mutex_lock(&i->forks[p->right_fork]);
	p->right_fork_timestamp_ms = timestamp_in_ms(p);
	if (!print_action(p->right_fork_timestamp_ms, p, i, FORK_MSG))
	{
		pthread_mutex_unlock(&i->forks[p->left_fork]);
		pthread_mutex_unlock(&i->forks[p->right_fork]);
		return (false);
	}
	return (true);
}

static bool	eating(t_philo *p, t_info *i)
{
	if (!print_action(p->right_fork_timestamp_ms, p, i, EAT_MSG))
	{
		pthread_mutex_unlock(&i->forks[p->left_fork]);
		pthread_mutex_unlock(&i->forks[p->right_fork]);
		return (false);
	}
	pthread_mutex_lock(&i->philo_mtx[p->id - 1]);
	p->time_of_last_meal = time_in_usec();
	precise_sleep(i->time_to_eat);
	p->time_of_last_meal = time_in_usec();
	p->meals_eaten++;
	pthread_mutex_unlock(&i->philo_mtx[p->id - 1]);
	pthread_mutex_unlock(&i->forks[p->right_fork]);
	pthread_mutex_unlock(&i->forks[p->left_fork]);
	return (true);
}

static bool	sleeping(t_philo *p, t_info *i)
{
	if (!print_action(timestamp_in_ms(p), p, i, SLEEP_MSG))
		return (false);
	precise_sleep(i->time_to_sleep);
	return (true);
}

static bool	thinking(t_philo *p, t_info *i)
{
	if (!print_action(timestamp_in_ms(p), p, i, THINK_MSG))
		return (false);
	return (true);
}

void	*life(void *p)
{
	t_philo	*philo;
	t_info	*i;

	philo = (t_philo *)p;
	i = (t_info *)philo->info;
	set_start_time(philo, i);
	if (philo->id % 2 == 0)
	{
		thinking(p, i);
		usleep(150);
	}
	while (1)
	{
		if (!taking_forks(p, i))
			break ;
		if (!eating(p, i))
			break ;
		if (!sleeping(p, i))
			break ;
		if (!thinking(p, i))
			break ;
	}
	return (NULL);
}
