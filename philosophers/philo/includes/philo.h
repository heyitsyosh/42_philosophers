/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:43:19 by myoshika          #+#    #+#             */
/*   Updated: 2022/11/05 12:23:31 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> //printf
# include <string.h> //memset
# include <stdlib.h> //malloc, free
# include <unistd.h> //read, write, usleep
# include <sys/time.h> //gettimeofday
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_philosopher{
	t_info		*i;
	pthread_t	tid;
	int			id;
	int			left_fork;
	int			right_fork;
	size_t		meals_eaten;
}	t_philosopher;

typedef struct s_info{
	int			num_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			max_meals;
	int			start_time;
	pthread_t	*forks;
	bool		overflow;
}	t_info;

bool	convert_input(int argc, char **argv, t_info *p);
int		philo_atoi(const char *str, t_info *p);
void	*life(void *p);

#endif