/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_i.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:48:58 by myoshika          #+#    #+#             */
/*   Updated: 2023/02/03 06:15:41 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

void	set_start_time(t_philo *philo, t_info *info)
{
	philo->start_time_ms = time_in_ms();
	sem_wait(info->sem_lock[philo->id - 1]);
	philo->time_of_last_meal = time_in_ms();
	sem_post(info->sem_lock[philo->id - 1]);
}

void	print_action(long time, t_philo *philo, t_info *info, char *action)
{
	sem_wait(info->sem_print);
	printf("%ld %d %s\n", time, philo->id, action);
	sem_post(info->sem_print);
}

void	sleep_till(long target_time_ms, t_philo *philo)
{
	while (timestamp_in_ms(philo) < target_time_ms)
		usleep(100);
}

static void	put_in_digits(char *arr, long buf)
{
	int	div;

	div = 1;
	if (buf < 0)
	{
		*arr = '-';
		buf *= -1;
		arr++;
	}
	while (buf / 10 >= div)
		div *= 10;
	while (div != 0)
	{
		*arr = (buf / div) + '0';
		buf %= div;
		div /= 10;
		arr++;
	}
	*(arr) = '\0';
}

char	*ft_itoa(int n)
{
	char	*arr;
	long	buf;
	int		digits;	

	digits = 0;
	if (n < 0 || n == 0)
		digits++;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	arr = (char *)malloc(digits + 1);
	buf = (long)n;
	if (arr != NULL)
		put_in_digits(arr, buf);
	return (arr);
}
