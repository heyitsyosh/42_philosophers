/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:48:58 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/24 06:56:49 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

void	set_start_time(t_philo *philo, t_info *info)
{
	philo->start_time_ms = time_in_ms();
	sem_wait(info->sem_lock);
	philo->time_of_last_meal = time_in_ms();
	sem_post(info->sem_lock);
}

bool	print_action(long time, t_philo *philo, t_info *info, char *action)
{
	sem_wait(info->sem_print);
	if (info->should_exit)
	{
		sem_post(info->sem_print);
		return (false);
	}
	printf("%ld %d %s\n", time, philo->id, action);
	sem_post(info->sem_print);
	return (true);
}

void	sleep_till(long target_time_ms, t_philo *philo)
{
	while (timestamp_in_ms(philo) < target_time_ms)
		usleep(100);
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
