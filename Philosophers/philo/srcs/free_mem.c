/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youyoon <youyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:19:17 by youyoon           #+#    #+#             */
/*   Updated: 2023/08/10 13:19:17 by youyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_philo(t_monitor *monitor, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_destroy(&(monitor->philo[i].m_last_eat));
		pthread_mutex_destroy(&(monitor->philo[i].m_cnt_eat));
		i++;
	}
	free(monitor->philo);
	return (-1);
}

void	free_fork(t_monitor *monitor, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
		pthread_mutex_destroy(&(monitor->m_fork[i++]));
	free(monitor->m_fork);
	free(monitor->fork);
}

void	join_thread(t_monitor *monitor)
{
	int	i;
	int	status;

	i = 0;
	while (i < monitor->num_of_philo)
	{
		if (monitor->thread[i] != NULL)
			pthread_join(monitor->thread[i], (void *)&status);
		i++;
	}
	free(monitor->thread);
}

int	free_monitor(t_monitor *monitor)
{
	free_philo(monitor, monitor->num_of_philo);
	free_fork(monitor, monitor->num_of_philo);
	pthread_mutex_destroy(&(monitor->m_print));
	return (0);
}
