/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruben <ruben@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:59:08 by rhiguita          #+#    #+#             */
/*   Updated: 2025/10/31 00:21:38 by ruben            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
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
    struct s_sim     *sim;       // Puntero a la simulación general. 
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

    t_philo         *philos;
    pthread_mutex_t *forks;
    pthread_mutex_t write_mutex; //Mutex para proteger printf
    pthread_mutex_t sim_mutex;
    
}	t_sim;


// time.c

long    get_current_time(void);
void    precise_usleep(long time_in_ms, t_sim *sim); 
long    get_time_since(long start_time);

// utils.c

void    print_status(t_philo *philo, const char *status);
void    display_error(char *message);
long	ft_atol(const char *str);
size_t  ft_strlen(char *s);

// Parser.c 

int parse_args(t_sim *sim, int ac, char **av);

// init.c

int init_simulation(t_sim *sim);

// main.c

int main(int ac, char **av);

// Simulation.c

void	*philo_routine(void *arg);
int	start_simulation(t_sim *sim);

#endif
