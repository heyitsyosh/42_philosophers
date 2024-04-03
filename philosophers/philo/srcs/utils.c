/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:48:58 by myoshika          #+#    #+#             */
/*   Updated: 2024/04/03 21:01:41 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h> //printf
#include <limits.h> //INT_MAX
#include <unistd.h> //usleep, write

void	set_start_time(t_philo *philo, t_info *i)
{
	philo->start_time_ms = time_in_ms();
	pthread_mutex_lock(&i->philo_mtx[philo->id - 1]);
	philo->time_of_last_meal = time_in_ms();
	pthread_mutex_unlock(&i->philo_mtx[philo->id - 1]);
}

bool	print_action(long time, t_philo *philo, t_info *info, char *action)
{
	pthread_mutex_lock(&info->print);
	if (info->should_exit)
	{
		pthread_mutex_unlock(&info->print);
		return (false);
	}
	printf("%ld %d %s\n", time, philo->id, action);
	pthread_mutex_unlock(&info->print);
	return (true);
}

void	sleep_till(long target_time_ms, t_philo *philo)
{
	while (timestamp_in_ms(philo) < target_time_ms)
		usleep(100);
}

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*(s + len) != '\0')
		len++;
	return (len);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	s_len;

	if (s == NULL)
		return ;
	s_len = ft_strlen(s);
	while (s_len > INT_MAX)
	{
		write(fd, s, INT_MAX);
		s += INT_MAX;
		s_len -= INT_MAX;
	}
	write(fd, s, s_len);
}
