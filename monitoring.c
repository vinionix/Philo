/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:41:18 by vfidelis          #+#    #+#             */
/*   Updated: 2025/04/02 13:41:18 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(long action, t_table *table)
{
	long long	start;

	start = get_current_time();
	while (get_current_time() - start < action)
	{
		if (!is_alive(table))
			break ;
		usleep(100);
	}
}

int	is_alive(t_table *node)
{
	int	alive;

	pthread_mutex_lock(&node->args->alive_mutex);
	alive = node->args->alive;
	pthread_mutex_unlock(&node->args->alive_mutex);
	return (alive);
}

long long	timey(t_table *table)
{
	return (get_current_time() - table->args->start_time);
}

int	ft_check_philosopher(t_table *table)
{
	long long	now;
	long long	time_elapsed;
	int			satisfied;

	now = timey(table);
	pthread_mutex_lock(&table->u_data.philo.meal_mutex);
	if (table->args->num_philos % 2 == 1)
		usleep(1000);
	time_elapsed = now - table->u_data.philo.last_meal;
	satisfied = table->u_data.philo.satisfied;
	pthread_mutex_unlock(&table->u_data.philo.meal_mutex);
	pthread_mutex_lock(&table->args->alive_mutex);
	if (time_elapsed > table->args->time_to_die)
	{
		table->args->alive = 0;
		print_status(table, "died");
		pthread_mutex_unlock(&table->args->alive_mutex);
		return (0);
	}
	pthread_mutex_unlock(&table->args->alive_mutex);
	return (1);
}

void	*ft_monitoring(void *args)
{
	t_table	*table;
	t_table	*start;
	int		all_satisfied;

	table = (t_table *)args;
	start = table;
	while (1)
	{
		if (table->type == PHILO)
		{
			if (ft_check_philosopher(table) == 0)
				return (NULL);
			pthread_mutex_lock(&table->args->num_philos_mutex);
			all_satisfied = table->args->num_philos == 0;
			pthread_mutex_unlock(&table->args->num_philos_mutex);
			if (all_satisfied)
				return (NULL);
		}
		table = table->next;
		if (table == start)
			usleep(10);
	}
	return (NULL);
}

