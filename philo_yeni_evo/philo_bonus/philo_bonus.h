/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:02:51 by mulken            #+#    #+#             */
/*   Updated: 2023/10/14 12:38:52 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <signal.h>

# define TAKEN_FORK "has taken a fork"
# define IS_EATING "is eating"
# define IS_SLEEPING "is sleeping"
# define IS_THINKING "is thinking"
# define DIE "died"

typedef struct s_philo
{
	uint64_t		id;
	uint64_t		last_eat;
	uint64_t		last_sleep;
	int				child;
	int				num_eat;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	sem_t			*forks;
	sem_t			*is_printing;
	sem_t			*is_dying;
	t_philo			*philos;
	uint64_t		time;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				number_of_philos;
	int				number_of_must_eat;
	int				stop;
}					t_table;

t_table			*parse(int ac, char **av);
uint64_t		time_from_start(t_table *table);
uint64_t		current_time(void);
int				must_eat_check(t_table *table);
int				is_digit(char *str);
int				err_msg(char *msg);
void			start_forks(t_table *table);
void			philo_routine(t_philo *philos);
void			print(t_philo *philo, char *str);
void			time_usleep(uint64_t micsec);
void			print_dead(t_philo *philo, char *str);
unsigned int	unsigned_atoi(char *str);
void			philo_free(t_philo *philo);

#endif
