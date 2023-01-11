/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:29:10 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/11 23:01:52 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>
#include <unistd.h>

void	print_action(t_philo *philo, t_info *info, char *action)
{
	pthread_mutex_lock(&info->print);
	printf("%ld %d %s\n", timestamp(philo), philo->id, action);
	pthread_mutex_unlock(&info->print);
}

static bool	eating(t_philo *p, t_info *i)
{
	if (should_end_thread(i))
		return (false);
	pthread_mutex_lock(&i->forks[p->left_fork]);
	print_action(p, i, FORK_MSG);
	if (should_end_thread(i))
	{
		pthread_mutex_unlock(&i->forks[p->left_fork]);
		return (false);
	}
	pthread_mutex_lock(&i->forks[p->right_fork]);
	pthread_mutex_lock(&i->print);
	printf("%ld %d %s\n", timestamp(p), p->id, FORK_MSG);
	printf("%ld %d %s\n", timestamp(p), p->id, EAT_MSG);
	pthread_mutex_unlock(&i->print);
	p->time_of_last_meal = time_in_ms();
	precise_sleep(timestamp(p) + i->time_to_eat, p);
	p->meals_eaten++;
	pthread_mutex_unlock(&i->forks[p->right_fork]);
	pthread_mutex_unlock(&i->forks[p->left_fork]);
	return (true);
}

static bool	sleeping(t_philo *p, t_info *i)
{
	if (should_end_thread(i))
		return (false);
	print_action(p, i, SLEEP_MSG);
	precise_sleep(timestamp(p) + i->time_to_sleep, p);
	return (true);
}

static bool	thinking(t_philo *p, t_info *i)
{
	if (should_end_thread(i))
		return (false);
	print_action(p, i, THINK_MSG);
	return (true);
}

void	*life(void *p)
{
	t_philo	*philo;
	t_info	*i;

	philo = (t_philo *)p;
	i = (t_info *)philo->info;
	philo->start_time = time_in_ms();
	philo->time_of_last_meal = philo->start_time;
	if (philo->id % 2 == 0)
	{
		thinking(p, i);
		usleep(200);
	}
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
