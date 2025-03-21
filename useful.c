/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:43:22 by vfidelis          #+#    #+#             */
/*   Updated: 2025/03/21 05:21:44 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *arg)
{
	long	num;
	int		i;

	i = 0;
	num = 0;
	while (arg[i])
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
			return (-1);
		i++;
	}
	i = 0;
	while (arg[i])
		num = num * 10 + (arg[i++] - '0');
	return (num);
}

t_table	*new_node(t_node_type type, t_args *args, int i)
{
	t_table	*new_node;

	new_node = malloc(sizeof(t_table));
	new_node->args = args;
	new_node->type = type;
	if (type == FORK)
	{
		new_node->u_data.fork.id = i;
		pthread_mutex_init(&new_node->u_data.fork.lock, NULL);
	}
	else if (type == PHILO)
	{
		new_node->u_data.philo.id = i;
		if (new_node->args->has_must_eat == 1)
			new_node->u_data.philo.satisfied = new_node->args->must_eat;
	}
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	lst_add_back(t_table **table, t_table *new_node)
{
	t_table	*last;

	if (new_node == NULL)
		return ;
	if (*table == NULL)
	{
		*table = new_node;
		new_node->next = new_node;
		new_node->prev = new_node;
		return ;
	}
	last = (*table)->prev;
	last->next = new_node;
	new_node->prev = last;
	new_node->next = *table;
	(*table)->prev = new_node;
	return ;
}
