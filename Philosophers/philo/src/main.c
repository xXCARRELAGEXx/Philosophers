/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrault <rrault@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:11:21 by rrault            #+#    #+#             */
/*   Updated: 2023/10/12 12:30:52 by rrault           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	error(void)
{
	write(2, "Error! invalid arguments\n", 26);
	return (1);
}

int	main(int argc, char *argv[])
{
	int			i;
	t_data		data;
	pthread_t	*id;

	if ((argc < 5 || argc > 6) || check_args(argc, argv, &data))
		return (error());
	id = (pthread_t *)malloc(data.nbr_philos * sizeof(pthread_t));
	data.t_0 = get_elapsed_time();
	i = -1;
	while (++i < data.nbr_philos)
	{
		if (pthread_create(&id[i], NULL, &cycle_life, &data.philos[i]))
		{
			write(2, "Error! cannot create thread\n", 28);
			free(data.philos);
			free(id);
			return (1);
		}
		pthread_mutex_lock(&data.check);
		data.philos[i].last_meal = data.t_0;
		pthread_mutex_unlock(&data.check);
	}
	check_death(&data);
	ft_exit(&data, id);
	return (0);
}
