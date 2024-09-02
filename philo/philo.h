/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:59:27 by mulken            #+#    #+#             */
/*   Updated: 2024/09/02 10:59:30 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_philo
{
	int				p_id;
	u_int64_t		last_eat;
	pthread_t		thread;
	size_t			eat_count;
	int				left_fork;
	int				right_fork;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	t_philo			*philo;
	int				philo_number;
	size_t			time_to_die;
	size_t			time_to_sleep;
	size_t			time_to_eat;
	size_t			eat_limit;
	int				die_id;
	int				eat_count;
	int				check_die;
	u_int64_t		die_time;
	u_int64_t		start;
	pthread_mutex_t	mutex_wait;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_print;
}					t_table;

int					argument_control(int ac, char **av, t_table *table);
int					create_mutex(t_table *table);
int					ft_strlen(char *str);
void				destroy_philo_forks(t_table *table);
int					init_philo(t_table *table);
int					die_control(t_table *table, t_philo *philo, int i);
int					print_philo(char *str, t_philo *philo);
void				ft_usleep(u_int64_t time);
u_int64_t			get_time_for_philo(void);
int					start_philo(t_table *table, int i);
int					ft_philo_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);

#endif