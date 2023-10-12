/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrault <rrault@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:11:07 by rrault            #+#    #+#             */
/*   Updated: 2023/10/12 12:08:26 by rrault           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	check_nbrs(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		if (argv[i][0] == '-')
			return (1);
		else if (argv[i][0] == '+')
			j++;
		if (!ft_isdigit(argv[i][j + 1]))
			return (1);
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
		}
	}
	return (0);
}

static int	check_int(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (*s == '+' && s++)
		len--;
	while (*s == '0' && *s && len--)
		s++;
	if (len > 10)
		return (1);
	else if (len < 10)
		return (0);
	if (ft_strncmp(s, "2147483648", 10) >= 0)
		return (1);
	return (0);
}

static int	valid_args(int argc, char *argv[])
{
	int	i;

	if (check_nbrs(argc, argv))
		return (1);
	i = 0;
	while (++i < argc)
	{
		if (check_int(argv[i]))
			return (1);
	}
	return (0);
}

static void	initialisation(t_data *data)
{
	int	i;

	data->death = 0;
	data->eaten_meals = 0;
	data->philos = (t_philo *)malloc(data->nbr_philos * sizeof(t_philo));
	i = -1;
	while (++i < data->nbr_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].nbr_eat = 0;
		if (i + 1 == data->nbr_philos)
			data->philos[i].next = &data->philos[0];
		else
			data->philos[i].next = &data->philos[i + 1];
		if (i == 0)
			data->philos[i].last = &data->philos[data->nbr_philos - 1];
		else
			data->philos[i].last = &data->philos[i - 1];
		pthread_mutex_init(&data->philos[i].fork, NULL);
	}
	pthread_mutex_init(&data->display, NULL);
	pthread_mutex_init(&data->check, NULL);
}

int	check_args(int argc, char *argv[], t_data *data)
{
	if (valid_args(argc, argv))
		return (1);
	data->nbr_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->nbr_meals = -1;
	if (argc == 6)
		data->nbr_meals = ft_atoi(argv[5]);
	initialisation(data);
	return (0);
}
