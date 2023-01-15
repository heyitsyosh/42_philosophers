/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:48:58 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/15 16:14:59 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

void	set_start_time(t_philo *philo, t_info *i)
{
	philo->start_time_ms = time_in_ms();
	pthread_mutex_lock(&i->philo_mtx[philo->id - 1]);
	philo->time_of_last_meal = time_in_usec();
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

void	precise_sleep(long target_time_usec)
{
	long	start_time_usec;

	start_time_usec = time_in_usec();
	while (1)
	{
		if (time_in_usec() - start_time_usec >= target_time_usec)
			break ;
		usleep(100);
	}
}

static int	make_int(const char *str, size_t i, int sign, t_info *info)
{
	long	num;

	num = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		if (sign == 1 && ((num > INT_MAX / 10)
				|| (num == INT_MAX / 10 && str[i] - '0' > INT_MAX % 10)))
			info->overflow = true;
		else if (sign == -1 && ((num < INT_MIN / 10)
				|| (num == INT_MIN / 10 && str[i] - '0' > INT_MIN % 10 * -1)))
			info->overflow = true;
		if (info->overflow)
			break ;
		num = (num * 10) + sign * (str[i] - '0');
		i++;
	}
	return ((int)num);
}

int	philo_atoi(const char *str, t_info *info)
{
	size_t	i;
	int		sign;

	sign = 1;
	i = 0;
	while (*(str + i) == 32 || (9 <= *(str + i) && *(str + i) <= 13))
		i++;
	if ((*(str + i) == '+' || *(str + i) == '-') && *(str + i))
	{
		if (*(str + i) == '-')
			sign = -1;
		i++;
	}
	return (make_int(str, i, sign, info));
}
