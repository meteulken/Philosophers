/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:06:15 by mulken            #+#    #+#             */
/*   Updated: 2023/10/14 12:37:23 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>

# define TAKEN_FORK "has taken a fork"
# define IS_EATING "is eating"
# define IS_SLEEPING "is sleeping"
# define IS_THINKING "is thinking"
# define DIE "died"

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	uint64_t		id;
	uint64_t		last_eat;
	uint64_t		last_sleep;
	int				sleeping;
	int				eating;
	int				num_eat;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	is_printing;
	pthread_mutex_t	is_dying;
	t_philo			*philos;
	uint64_t		time;
	uint64_t		time_to_die;
	int				number_of_philos;
	int				time_to_sleep;
	int				time_to_eat;
	int				number_of_must_eat;
	int				stop;
}					t_table;

t_table			*parse(int ac, char **av);
uint64_t		time_from_start(t_table *table);
uint64_t		current_time(void);
int				is_digit(char *str);
int				err_msg(char *msg);
void			creating_threads(t_table *table);
void			*routine(void *param);
void			check_death(t_table *table);
void			print(t_philo *philo, char *str);
void			time_usleep(uint64_t micsec);
unsigned int	unsigned_atoi(char *str);

#endif
