/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:19:22 by vfidelis          #+#    #+#             */
/*   Updated: 2025/04/03 17:43:14 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *args)
{
	t_table	*table;

	table = (t_table *)args;
	print_status(table, "taken a fork");
	ft_sleep(table->args->time_to_die, table);
	print_status(table, "died");
	return (NULL);
}
