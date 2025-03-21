/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:08:26 by vfidelis          #+#    #+#             */
/*   Updated: 2025/03/21 05:41:50 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_args	args;
	t_table	*table;

	table = NULL;
	if (argc < 5 || argc > 6)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	if (ft_initialize_args(&args, argc, argv) == 0)
		return (0);
	ft_initialize_table(&table, &args);
	for(int i = 0; i < 25; i++)
	{
		if (table->type == PHILO)
		{
			printf("Philo id: %d\n", table->u_data.philo.id);
			printf("Number_eat: %d\n\n", table->u_data.philo.satisfied);
		}
		else if (table->type == FORK)
			printf("Fork_id: %d\n\n", table->u_data.fork.id);
		table = table->next;
	}
}
