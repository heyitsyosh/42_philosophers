/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:29:10 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/27 01:39:05 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static bool	taking_forks(t_philo *p, t_info *i)
{
	if (i->num_of_philosophers == 1)
	{
		usleep(i->time_to_die + 800);
		return (false);
	}
	sem_wait(i->forks);
	sem_wait(i->forks);
	p->right_fork_timestamp_ms = timestamp_in_ms(p);
	if (!print_action(p->right_fork_timestamp_ms, p, i, FORK_MSG)
		|| !print_action(p->right_fork_timestamp_ms, p, i, EAT_MSG))
	{
		sem_post(i->forks);
		sem_post(i->forks);
		return (false);
	}
	return (true);
}

static bool	eating(t_philo *p, t_info *i)
{
	sem_wait(i->sem_lock);
	p->time_of_last_meal = time_in_ms();
	sem_post(i->sem_lock);
	sleep_till(p->right_fork_timestamp_ms + i->time_to_eat, p);
	sem_wait(i->sem_lock);
	p->meals_eaten++;
	if (i->meals_to_eat != -1 && p->meals_eaten == i->meals_to_eat)
		sem_post(i->ate_minimum_req);
	sem_post(i->sem_lock);
	sem_post(i->forks);
	sem_post(i->forks);
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
	return (true);
}

void	life(t_philo *p, t_info *i)
{
	set_start_time(p, i);
	if (i->meals_to_eat != -1)
		sem_wait(i->ate_minimum_req);
	if (p->id % 2 == 0
		|| (p->id == i->num_of_philosophers && i->num_of_philosophers != 1))
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
}
