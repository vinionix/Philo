/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:46:45 by vfidelis          #+#    #+#             */
/*   Updated: 2025/03/27 20:43:34 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    try_to_catch(t_table *table)
{
    pthread_mutex_lock(&table->prev->u_data.fork.lock);
	print_status(table, "has taken a fork");
    pthread_mutex_lock(&table->next->u_data.fork.lock);
	print_status(table, "has taken a fork");
}

void    drop_fork(t_table *table)
{
    pthread_mutex_unlock(&table->prev->u_data.fork.lock);
	pthread_mutex_unlock(&table->next->u_data.fork.lock);
}
static void	eat(t_table *table)
{
	try_to_catch(table);
	if (table->args->has_must_eat == 1)
		table->u_data.philo.satisfied--;
	print_status(table, "is eating");
	ft_sleep(table->args->time_to_eat);
	drop_fork(table);
}
static void	spleep(t_table *table)
{
	print_status(table, "is sleeping");
	ft_sleep(table->args->time_to_sleep);
}

void	*routine(void *args)
{
	t_table	*table;

	table = (t_table *)args;
	if (table->u_data.philo.id % 2 == 0)
		usleep(1000);
	while (table->args->has_must_eat == 0 || table->u_data.philo.satisfied > 0)
	{
		eat(table);
		if (is_alive(table) == 0)
			break ;
		spleep(table);
		if (is_alive(table) == 0)
			break ;
		print_status(table, "is thinking");
		if (is_alive(table) == 0)
			break ;
		usleep(1);
	}
	return (NULL);
}
