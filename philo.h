/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:09:25 by vfidelis          #+#    #+#             */
/*   Updated: 2025/03/21 05:21:31 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_philo_args
{
	long	num_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	must_eat;
	long	has_must_eat;
}			t_args;

typedef enum s_node_type
{
	PHILO,
	FORK
}	t_node_type;

typedef struct s_fork
{
	int				id;
	int				unlok;
	pthread_mutex_t	lock;
}					t_fork;

typedef struct s_philo
{
	pthread_t	phl;
	int			id;
	long long	last_meal;
	int			satisfied;

}				t_philo;

typedef struct s_table
{
	t_node_type		type;
	union
	{
		t_fork	fork;
		t_philo	philo;
	}				u_data;
	long long		start_time;
	t_args			*args;
	struct s_table	*prev;
	struct s_table	*next;
}					t_table;

long	ft_atoi(char *arg);
int		ft_initialize_args(t_args *args, int argc, char **argv);
void	lst_add_back(t_table **table, t_table *new_node);
void	ft_initialize_table(t_table **table, t_args *args);
t_table	*new_node(t_node_type type, t_args *args, int i);

#endif