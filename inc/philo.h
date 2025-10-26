/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruben <ruben@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:59:08 by rhiguita          #+#    #+#             */
/*   Updated: 2025/10/26 09:26:15 by rhiguita         ###   ########.fr       */
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
	int     num_philos;                 
    int     num_meals_to_eat;           //Argumento opcional.
    int     simulation_should_end;      //Flag de muerte/Fin.
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    long    start_time;

    t_philo *philos;
    pthread_mutex_t *forks;
    pthread_mutex_t write_mutex; //Mutex para proteger printf
    pthread_mutex_t sim_mutex;
    
}	t_sim;

#endif




















