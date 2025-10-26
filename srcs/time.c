/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 08:25:53 by rhiguita          #+#    #+#             */
/*   Updated: 2025/10/26 08:25:56 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    get_current_time(void)
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) != 0)
    {
        printf("Error: gettimeofday falló\n");
        return (0);
    }
    return (())
}
