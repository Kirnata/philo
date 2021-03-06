/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptopping <ptopping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:40:34 by ptopping          #+#    #+#             */
/*   Updated: 2022/06/28 20:45:59 by ptopping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include "../inc/messages.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	int		i;

	i = 0;
	if (data_init(&data, argc, argv) == FALSE)
		return (FALSE);
	if (mutex_create(&data) == FALSE)
		return (FALSE);
	if (create_philo(&data) == FALSE)
		return (FALSE);
	if (create_philo_threads(&data) == FALSE)
		return (FALSE);
	if (ft_mutex_unlock(&data) == FALSE)
		return (FALSE);
	if (join_threads(&data) == FALSE)
		return (FALSE);
	if (ft_mutex_destroy(&data) == FALSE)
		return (FALSE);
	philo_free(&data);
	printf("😎 ENDING SIMULATION 😎\n");
	return (0);
}

int	ft_mutex_unlock(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_unlock(&data->mtxs[i]);
		i++;
	}
	pthread_mutex_unlock(data->mutex_for_check);
	pthread_mutex_unlock(data->mutex_for_print);
	return (0);
}

int	(ft_mutex_destroy(t_data *data))
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_destroy(&data->mtxs[i]))
			return (FALSE);
		i++;
	}
	if (pthread_mutex_destroy(data->mutex_for_print))
		return (FALSE);
	if (pthread_mutex_destroy(data->mutex_for_check))
		return (FALSE);
	return (TRUE);
}

void	philo_free(t_data *data)
{
	free(data->philo_data);
	free(data->mutex_for_print);
	free(data->mutex_for_check);
	free(data->mtxs);
}
