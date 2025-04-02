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

void try_to_catch(t_table *table)
{
    if (table->prev->u_data.fork.id < table->next->u_data.fork.id)
    {
        pthread_mutex_lock(&table->next->u_data.fork.lock);
        if (!is_alive(table))
        {
            pthread_mutex_unlock(&table->next->u_data.fork.lock);
            return ;
        }
        print_status(table, "has taken a fork");
        pthread_mutex_lock(&table->prev->u_data.fork.lock);
        if (!is_alive(table))
        {
            pthread_mutex_unlock(&table->next->u_data.fork.lock);
            pthread_mutex_unlock(&table->prev->u_data.fork.lock);
            return ;
        }
        print_status(table, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&table->prev->u_data.fork.lock);
        if (!is_alive(table))
        {
            pthread_mutex_unlock(&table->prev->u_data.fork.lock);
            return ;
        }
        print_status(table, "has taken a fork");
        pthread_mutex_lock(&table->next->u_data.fork.lock);
        if (!is_alive(table))
        {
            pthread_mutex_unlock(&table->next->u_data.fork.lock);
            pthread_mutex_unlock(&table->prev->u_data.fork.lock);
            return ;
        }
        print_status(table, "has taken a fork");
    }
}

void    drop_fork(t_table *table)
{
	pthread_mutex_unlock(&table->prev->u_data.fork.lock);
	pthread_mutex_unlock(&table->next->u_data.fork.lock);
}
static void eat(t_table *table)
{
	try_to_catch(table);
    if (!is_alive(table))
    {
        return ;
    }
	pthread_mutex_lock(&table->u_data.philo.meal_mutex);
	table->u_data.philo.last_meal = timey(table);
	if (table->args->has_must_eat == 1)
	{
		table->u_data.philo.satisfied--;
		if (table->u_data.philo.satisfied == 0)
		{
			pthread_mutex_lock(&table->args->num_philos_mutex);
			table->args->num_philos--;
			pthread_mutex_unlock(&table->args->num_philos_mutex);
		}
	}
	pthread_mutex_unlock(&table->u_data.philo.meal_mutex);
	print_status(table, "is eating");
	ft_sleep(table->args->time_to_eat, table);
	drop_fork(table);
}
static void	spleep(t_table *table)
{
	print_status(table, "is sleeping");
	ft_sleep(table->args->time_to_sleep, table);
}

void *routine(void *args)
{
    t_table *table;
	int		satisfied;

    table = (t_table *)args;
    if (table->u_data.philo.id % 2 == 0)
        usleep(100);
    while (is_alive(table))
    {
        pthread_mutex_lock(&table->u_data.philo.meal_mutex);
        satisfied = table->u_data.philo.satisfied;
        pthread_mutex_unlock(&table->u_data.philo.meal_mutex);
        if (table->args->has_must_eat == 1 && satisfied == 0)
			break ;
        eat(table);
        if (!is_alive(table))
			break ;
        spleep(table);
        if (!is_alive(table))
			break ;
        print_status(table, "is thinking");
    }
    return (NULL);
}
