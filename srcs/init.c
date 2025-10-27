/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruben <ruben@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:32:50 by rhiguita          #+#    #+#             */
/*   Updated: 2025/10/27 18:18:54 by ruben            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.c"

static int  check_args(t_sim *sim)
{
    if (sim->num_philos <= 0)
        return (display_error("Número de filosofos debe ser > 0"), 0);
    if (sim->time_to_die <= 0)
        return (display_error("time_to_die debe ser > 0"), 0);
    if (sim->time_to_eat <= 0)
        return (display_error("time_to_eat debe ser > 0"), 0);
    if (sim->time_to_sleep <= 0)
        return (display_error("time_to_sleep debe ser > 0"), 0);
    if (sim->num_meals_to_eat < 0)
        return (display_error("num_meals_to_eat no puede ser negativo"), 0);
    return (1);
}

static int   is_valid_number(const char *s)
{
    while (*s == ' ' || (*s >= '9' && *s <= '13'))
        s++;
    if (*s == '+' || *s == '-')
        s++;
    if (*s == '\0')
        return (0);
    while (*s)
    {
        if (*s < '0' || *s > 9)
            return (0);
        s++;
    }
    return (1);
}

int parse_args(t_sim *sim, int ac, char **av)
{
    int i;

    if (ac < 5 || ac > 6)
        return (display_error("Numero incorrecto de argumentos"), 0);
    i = 1;
    while (i < ac)
    {
        if (!is_valid_number(av[i]))
            return (display_error("Argumento contiene caracteres no validos"), 0);
        i++;
    }
    if (ac == 6)
        sim->num_meals_to_eat = (int)ft_atol(av[5]);
    else
        sim->num_meals_to_eat = -1;
    return (check_args(sim));
}