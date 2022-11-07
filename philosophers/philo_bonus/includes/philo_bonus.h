/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:43:21 by myoshika          #+#    #+#             */
/*   Updated: 2022/11/07 06:59:59 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h> //printf
# include <string.h> //memset
# include <stdlib.h> //malloc, free, exit
# include <unistd.h> //read, write, usleep, fork
# include <stdbool.h>
# include <sys/time.h> //gettimeofday
# include <signal.h> //kill
# include <pthread.h>
# include <sys/types.h>
# include <sys/wait.h> //waitpid
# include <fcntl.h> //For O_* constants
# include <sys/stat.h> //For mode constants
# include <semaphore.h>

# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DIE_MSG "died"

typedef struct s_philo{
	t_info		*i;
	pthread_t	tid;
	int			id;
	int			left_fork;
	int			right_fork;
	size_t		meals_eaten;
}	t_philo;

typedef struct s_info{
	int				num_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	long			start_time;
	bool			overflow;
}	t_info;

#endif