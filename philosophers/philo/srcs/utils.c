/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:48:58 by myoshika          #+#    #+#             */
/*   Updated: 2022/11/09 14:32:29 by myoshika         ###   ########.fr       */
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

// void	precise_sleep(long target_time, t_philo *p)
// {
// 	long	start_time;

// 	start_time = timestamp(p);
// 	while (1)
// 	{
// 		if (timestamp(p) - start_time >= target_time)
// 			break ;
// 		usleep(1); //micro,usec; microsecond > millisecond
// 	}
// }

void	print_action(t_philo *philo, t_info *i, char *action)
{
	pthread_mutex_lock(&i->print);
	printf("%ld %d %s\n", timestamp(philo), philo->id, action);
	pthread_mutex_unlock(&i->print);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t				i;
	const unsigned char	*uc_s1 = (const unsigned char*)s1;
	const unsigned char	*uc_s2 = (const unsigned char*)s2;

	i = 0;
	while (*(uc_s1 + i) && *(uc_s2 + i))
	{
		if (*(uc_s1 + i) != *(uc_s2 + i))
			break ;
		i++;
	}
	return (*(uc_s1 + i) - *(uc_s2 + i));
}
