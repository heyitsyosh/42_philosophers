/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:29:10 by myoshika          #+#    #+#             */
/*   Updated: 2024/04/03 20:59:08 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <unistd.h> //usleep

static bool	taking_forks(t_philo *p, t_info *i)
{
	pthread_mutex_lock(&i->forks[p->left_fork]);
	if (!print_action(timestamp_in_ms(p), p, i, FORK_MSG)
		|| i->num_of_philosophers == 1)
	{
		pthread_mutex_unlock(&i->forks[p->left_fork]);
		if (i->num_of_philosophers == 1)
			usleep(i->time_to_die * 1000 + 5000);
		return (false);
	}
	pthread_mutex_lock(&i->forks[p->right_fork]);
	p->right_fork_timestamp_ms = timestamp_in_ms(p);
	if (!print_action(p->right_fork_timestamp_ms, p, i, FORK_MSG))
	{
		pthread_mutex_unlock(&i->forks[p->right_fork]);
		pthread_mutex_unlock(&i->forks[p->left_fork]);
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
	p->time_of_last_meal = time_in_ms();
	pthread_mutex_unlock(&i->philo_mtx[p->id - 1]);
	sleep_till(p->right_fork_timestamp_ms + i->time_to_eat, p);
	pthread_mutex_unlock(&i->forks[p->right_fork]);
	pthread_mutex_unlock(&i->forks[p->left_fork]);
	pthread_mutex_lock(&i->philo_mtx[p->id - 1]);
	p->meals_eaten++;
	pthread_mutex_unlock(&i->philo_mtx[p->id - 1]);
	return (true);
}

static bool	sleeping(t_philo *p, t_info *i)
{
	long	sleeping_start_time;

	sleeping_start_time = timestamp_in_ms(p);
	if (!print_action(sleeping_start_time, p, i, SLEEP_MSG))
		return (false);
	sleep_till(sleeping_start_time + i->time_to_sleep, p);
	return (true);
}

static bool	thinking(t_philo *p, t_info *i)
{
	if (!print_action(timestamp_in_ms(p), p, i, THINK_MSG))
		return (false);
	usleep(100);
	return (true);
}

void	*life(void *p)
{
	t_philo	*philo;
	t_info	*i;

	philo = (t_philo *)p;
	i = (t_info *)philo->info;
	set_start_time(philo, i);
	if (philo->id % 2 == 0
		|| (philo->id == i->num_of_philosophers && i->num_of_philosophers != 1))
	{
		thinking(p, i);
		usleep(70);
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
