/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrault <rrault@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:11:24 by rrault            #+#    #+#             */
/*   Updated: 2023/10/12 12:48:24 by rrault           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	is_full(t_data *data, int i)
{
	if (i == data->nbr_philos)
		data->eaten_meals = 1;
}

void	check_death(t_data *data)
{
	int	i;

	while (!data->eaten_meals)
	{
		i = -1;
		while (!data->death && ++i < data->nbr_philos)
		{
			pthread_mutex_lock(&data->check);
			if (get_elapsed_time()
				- data->philos[i].last_meal > (size_t)data->time_to_die)
			{
				print_message(&data->philos[i], MESSAGE_DEATH);
				data->death = 1;
			}
			pthread_mutex_unlock(&data->check);
			usleep(100);
		}
		if (data->death)
			break ;
		i = 0;
		while (data->nbr_meals != -1 && i < data->nbr_philos
			&& data->philos[i].nbr_eat >= data->nbr_meals)
			i++;
		is_full(data, i);
	}
}

void	ft_exit(t_data *data, pthread_t *id)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philos)
		pthread_join(id[i], NULL);
	i = -1;
	while (++i < data->nbr_philos)
		pthread_mutex_destroy(&data->philos[i].fork);
	pthread_mutex_destroy(&data->display);
	pthread_mutex_destroy(&data->check);
	free(data->philos);
	free(id);
	if (data->eaten_meals)
		printf("\033[1;92mAll philosophers have eaten\033[1;92m");
}

size_t	get_elapsed_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_usleep(t_data *data, size_t time)
{
	size_t	t;

	t = get_elapsed_time();
	while (!(data->death))
	{
		if (get_elapsed_time() - t >= time)
			break ;
		usleep(100);
	}
}
