/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:09:25 by vfidelis          #+#    #+#             */
/*   Updated: 2025/03/26 15:35:55 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo_args
{
	pthread_mutex_t	print;
	pthread_mutex_t	alive_mutex;
	pthread_mutex_t	num_philos_mutex;
	long long		start_time;
	long			num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat;
	long			has_must_eat;
	long			alive;
}					t_args;

typedef enum s_node_type
{
	PHILO,
	FORK
}	t_node_type;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	lock;
}					t_fork;

typedef struct s_philo
{
	pthread_t		phl;
	int				id;
	long long		last_meal;
	int				satisfied;
	pthread_mutex_t	meal_mutex;
}					t_philo;

typedef struct s_table
{
	t_node_type		type;
	union
	{
		t_fork	fork;
		t_philo	philo;
	}				u_data;
	t_args			*args;
	struct s_table	*prev;
	struct s_table	*next;
}					t_table;

long long	get_current_time(void);
long long	timey(t_table *table);
long		ft_atoi(char *arg);
int			ft_initialize_args(t_args *args, int argc, char **argv);
int			is_alive(t_table *node);
t_table		*new_node(t_node_type type, t_args *args, int i);
void		lst_add_back(t_table **table, t_table *new_node);
void		ft_initialize_table(t_table **table, t_args *args);
void		ft_free_all(t_table *table);
void		print_status(t_table *table, char *status);
void		ft_sleep(long action, t_table *table);
void		*routine(void *args);
void		*ft_monitoring(void *args);

#endif