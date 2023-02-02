/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ii.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:03:43 by myoshika          #+#    #+#             */
/*   Updated: 2023/02/03 04:00:55 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

void	print_error_and_exit(char *error_message)
{
	ft_putstr_fd(error_message, STDERR_FILENO);
	exit(EXIT_FAILURE);
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
