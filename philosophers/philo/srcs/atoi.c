/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 22:06:16 by myoshika          #+#    #+#             */
/*   Updated: 2022/11/05 11:20:23 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_whitespace(char c)
{
	return (c == 32 || (9 <= c && c <= 13));
}

static int	make_l(const char *str, size_t i, int sign, t_info *p)
{
	long	num;

	num = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		if (sign == 1 && ((num > LONG_MAX / 10)
				|| (num == LONG_MAX / 10 && str[i] - '0' > LONG_MAX % 10)))
			p->overflow = true;
		else if (sign == -1 && ((num < LONG_MIN / 10)
				|| (num == LONG_MIN / 10 && str[i] - '0' > LONG_MIN % 10 * -1)))
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
	while (is_whitespace(*(str + i)))
		i++;
	if ((*(str + i) == '+' || *(str + i) == '-') && *(str + i))
	{
		if (*(str + i) == '-')
			sign = -1;
		i++;
	}
	return (make_l(str, i, sign, p));
}
