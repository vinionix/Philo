/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:48:08 by vfidelis          #+#    #+#             */
/*   Updated: 2025/03/27 20:53:28 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_sleep(long action)
{
	long long	start;

	start = get_current_time() + action;
	while(get_current_time() < start)
		usleep(100);
}

int	is_alive(t_table *node)
{
	pthread_mutex_lock(&node->args->alive_mutex);
	if (node->args->alive == 0)
	{
		pthread_mutex_unlock(&node->args->alive_mutex);	
		return (0);
	}
	pthread_mutex_unlock(&node->args->alive_mutex);
	return (1);
}
long long timey(t_table *table)
{
	return (get_current_time() - table->args->start_time);
}

void    *ft_monitoring(void *args)
{
	t_table		*table;
	long long	time_elapsed;
	long long	now;
	long		end_dinner;

	table = (t_table *)args;
	end_dinner = table->args->num_philos;
	while(table->next)
	{
		if (table->type == PHILO)
		{
			if (table->args->has_must_eat == 1 && table->u_data.philo.satisfied == 0)
			{
				end_dinner--;
				if (end_dinner == 0)
					return (NULL);
			}
			now = timey(table);
			time_elapsed = now - table->u_data.philo.last_meal;
			if (time_elapsed >= table->args->time_to_die)
			{
				table->args->alive = 0;
				print_status(table, "died");
				return (NULL);
			}
		}
		table = table->next;
	}
	return (NULL);
}
