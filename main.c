/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:08:26 by vfidelis          #+#    #+#             */
/*   Updated: 2025/03/27 20:37:17 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_args		args;
	t_table		*table;
	t_table		*aux;
	pthread_t	mot;

	table = NULL;
	if (argc < 5 || argc > 6)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	if (ft_initialize_args(&args, argc, argv) == 0)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	ft_initialize_table(&table, &args);
	aux = table->prev;
	args.start_time = get_current_time();
	if (table->args->num_philos == 1)
	{
		pthread_create(&table->u_data.philo.phl, NULL, one_philo, table);
		pthread_join(table->u_data.philo.phl, NULL);
		ft_free_all(table);
		return (0);
	}
	while (table != aux)
	{
		if (table->type == PHILO)
		{
			table->u_data.philo.last_meal = args.start_time;
			pthread_create(&table->u_data.philo.phl, NULL, routine, table);
		}
		table = table->next;
	}
	pthread_create(&mot, NULL, ft_monitoring, table);
	table = table->next;
	while (table != aux)
	{
		if (table->type == PHILO)
			pthread_join(table->u_data.philo.phl, NULL);
		table = table->next;
	}
	pthread_join(mot, NULL);
	ft_free_all(table);
}
