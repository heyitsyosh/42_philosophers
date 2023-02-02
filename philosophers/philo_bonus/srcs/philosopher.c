/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:29:10 by myoshika          #+#    #+#             */
/*   Updated: 2023/02/03 04:15:28 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void	taking_forks(t_philo *p, t_info *i)
{
	sem_wait(i->forks);
	print_action(timestamp_in_ms(p), p, i, FORK_MSG);
	if (i->num_of_philosophers == 1)
		usleep(i->time_to_die * 1000 + 5000);
	sem_wait(i->forks);
	p->right_fork_timestamp_ms = timestamp_in_ms(p);
	print_action(p->right_fork_timestamp_ms, p, i, FORK_MSG);
	print_action(p->right_fork_timestamp_ms, p, i, EAT_MSG);
}

static void	eating(t_philo *p, t_info *i)
{
	sem_wait(i->sem_lock[p->id]);
	p->time_of_last_meal = time_in_ms();
	sem_post(i->sem_lock[p->id]);
	sleep_till(p->right_fork_timestamp_ms + i->time_to_eat, p);
	sem_wait(i->sem_lock[p->id]);
	p->meals_eaten++;
	if (i->meals_to_eat != -1 && p->meals_eaten == i->meals_to_eat)
		sem_post(i->ate_minimum_req);
	sem_post(i->sem_lock[p->id]);
	sem_post(i->forks);
	sem_post(i->forks);
}

static void	sleeping(t_philo *p, t_info *i)
{
	long	sleeping_start_time;

	sleeping_start_time = timestamp_in_ms(p);
	print_action(sleeping_start_time, p, i, SLEEP_MSG);
	sleep_till(sleeping_start_time + i->time_to_sleep, p);
}

static void	thinking(t_philo *p, t_info *i)
{
	print_action(timestamp_in_ms(p), p, i, THINK_MSG);
}

void	life(t_philo *p, t_info *i)
{
	set_start_time(p, i);
	make_starvation_monitor(p, i);
	if (p->id % 2 == 0
		|| (p->id == i->num_of_philosophers && i->num_of_philosophers != 1))
	{
		thinking(p, i);
		usleep(70);
	}
	while (1)
	{
		taking_forks(p, i);
		eating(p, i);
		sleeping(p, i);
		thinking(p, i);
	}
}
