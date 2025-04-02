/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:37:48 by vfidelis          #+#    #+#             */
/*   Updated: 2025/04/02 13:37:48 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((long long)tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_table *table, char *status)
{
	pthread_mutex_lock(&table->args->print);
	printf("%lld %d %s\n", get_current_time() - table->args->start_time,
		table->u_data.philo.id, status);
	pthread_mutex_unlock(&table->args->print);
}
