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

void ft_sleep(long action, t_table *table)
{
    long long start = get_current_time();
    while (get_current_time() - start < action)
    {
        if (!is_alive(table))
            break;
        usleep(100);
    }
}
int is_alive(t_table *node)
{
    int alive;

    pthread_mutex_lock(&node->args->alive_mutex);
    alive = node->args->alive;
    pthread_mutex_unlock(&node->args->alive_mutex);
    return (alive);
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
	t_table		*start;
	int 		satisfied;

	table = (t_table *)args;
	start = table;
	while(1)
	{
		if (table->type == PHILO)
		{
			now = timey(table);
			pthread_mutex_lock(&table->u_data.philo.meal_mutex);
			time_elapsed = now - table->u_data.philo.last_meal;
			pthread_mutex_unlock(&table->u_data.philo.meal_mutex);
			pthread_mutex_lock(&table->args->alive_mutex);
            pthread_mutex_lock(&table->u_data.philo.meal_mutex);
            satisfied = table->u_data.philo.satisfied;
            pthread_mutex_unlock(&table->u_data.philo.meal_mutex);
			if (time_elapsed > table->args->time_to_die)
			{
				table->args->alive = 0;
				print_status(table, "died");
				pthread_mutex_unlock(&table->args->alive_mutex);
				return (NULL);
			}
			if (table->args->has_must_eat == 1 && satisfied == 0)
			{
				pthread_mutex_lock(&table->args->num_philos_mutex);
				if (table->args->num_philos == 0)
				{
					pthread_mutex_unlock(&table->args->alive_mutex);
					pthread_mutex_unlock(&table->args->num_philos_mutex);
					usleep(1000000);
					return (NULL);
				}
				pthread_mutex_unlock(&table->args->num_philos_mutex);
			}
			pthread_mutex_unlock(&table->args->alive_mutex);
		}
		if (table == start)
			usleep(1);
		table = table->next;
	}
	return (NULL);
}
