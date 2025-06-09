/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:58:15 by rhiguita          #+#    #+#             */
/*   Updated: 2025/06/09 18:57:41 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

#define NUM_HILOS 2
#define ITERACIONES 100000

int contador = 0; // Variable global compartida
pthread_mutex_t mutex; // Declaración del mutex

// Función que ejecuta cada hilo
void* incrementar(void* data __attribute__((unused))) {
    for (int i = 0; i < ITERACIONES; i++) {
        pthread_mutex_lock(&mutex); // Bloquear el mutex
        contador++; // Sección crítica
        pthread_mutex_unlock(&mutex); // Desbloquear el mutex
    }
    return NULL;
}

int main() {
    pthread_t hilos[NUM_HILOS];

    // Inicializar el mutex
    pthread_mutex_init(&mutex, NULL);

    // Crear los hilos
    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_create(&hilos[i], NULL, incrementar, NULL);
    }

    // Esperar a que los hilos terminen
    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    // Imprimir el resultado
    printf("Valor final del contador: %d (Esperado: %d)\n", contador, NUM_HILOS * ITERACIONES);

    // Destruir el mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
