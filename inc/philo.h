/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruben <ruben@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:59:08 by rhiguita          #+#    #+#             */
/*   Updated: 2025/10/26 00:38:19 by ruben            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo // Datos de cada filisofo.
{
    
    pthread_t   thread;         //hilo del filosofo.
    int         id;             //ID del filoso (1 a N).
    int         meals_eating;   //contador de comidas.
    long        last_meal_time; //tiempo de la ultima comida.
    pthread_mutex_t *left_fork; //tenedor izquierdo.
    pthread_mutex_t *right_fork;//tenedor derecho.
//  strct s_sim     *sim;       // Puntero a la simulación general. 
} t_philo;

// Estructura s_sim
typedef struct s_sim
{
	int pid;

}	t_sim;

#endif
