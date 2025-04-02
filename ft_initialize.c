/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:40:04 by vfidelis          #+#    #+#             */
/*   Updated: 2025/03/27 18:44:37 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_initialize_table(t_table **table, t_args *args)
{
	int		i;

	i = 1;
	while (i <= (args->num_philos))
	{
		lst_add_back(table, new_node(PHILO, args, i));
		lst_add_back(table, new_node(FORK, args, i));
		i++;
	}
	return ;
}

int	ft_initialize_args(t_args *args, int argc, char **argv)
{
	args->num_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		args->must_eat = ft_atoi(argv[5]);
		if (args->must_eat <= 0)
			return (0);
		args->has_must_eat = 1;
	}
	else
		args->has_must_eat = 0;
	if (args->num_philos <= 0 || args->time_to_die <= 0
		|| args->time_to_eat <= 0 || args->time_to_sleep <= 0)
		return (0);
	args->alive = 1;
	pthread_mutex_init(&args->alive_mutex, NULL);
	pthread_mutex_init(&args->print, NULL);
	pthread_mutex_init(&args->num_philos_mutex, NULL);
	return (1);
}
