/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:48:58 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/10 11:56:48 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

long	timestamp(t_philo *philo)
{
	return (time_in_ms() - philo->start_time);
}

//philo = ms,usleep = usec/micro; microsecond < millisecond
void	precise_sleep(long target_time, t_philo *p)
{
	long	start_time;

	start_time = timestamp(p);
	while (1)
	{
		if (timestamp(p) - start_time >= target_time)
			break ;
		usleep(100);
	}
}

static int	make_l(const char *str, size_t i, int sign, t_info *p)
{
	long	num;

	num = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		if (sign == 1 && ((num > INT_MAX / 10)
				|| (num == INT_MAX / 10 && str[i] - '0' > INT_MAX % 10)))
			p->overflow = true;
		else if (sign == -1 && ((num < INT_MIN / 10)
				|| (num == INT_MIN / 10 && str[i] - '0' > INT_MIN % 10 * -1)))
			p->overflow = true;
		if (p->overflow)
			break ;
		num = (num * 10) + sign * (str[i] - '0');
		i++;
	}
	return ((int)num);
}

int	philo_atoi(const char *str, t_info *p)
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
	return (make_l(str, i, sign, p));
}
