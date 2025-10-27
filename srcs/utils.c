/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruben <ruben@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 08:26:19 by rhiguita          #+#    #+#             */
/*   Updated: 2025/10/27 16:48:08 by ruben            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	ft_atol(const char *str)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
	while (*str >= '0' && *str <= '9')
	{
        num = num * 10 + (*str - '0');
        str++;
    }
	return (num * sign);
}

size_t  ft_strlen(char *s)
{
    size_t  i;
    
    i = 0;
    while (s[i] != '\0')
        i++;
    return (i);
}

void    display_error(char *message)
{
    write(2, "Error: ", 7);
    write(2, message, ft_strlen(message));
    write(2, "\n", 1);
}

void    print_status(t_philo *philo, const char *status)
{
    long    timestam;
    
    pthread_mutex_lock(&philo->sim->write_mutex);
    timestam = get_time_since(philo->sim->start_time);
    if (!philo->sim->simulation_should_end)
    {
        printf("%ld %d %s\n", timestam, philo->id, status);
    }
    pthread_mutex_unlock(&philo->sim->sim_mutex);
    pthread_mutex_unlock(&philo->sim->write_mutex); 
}



















