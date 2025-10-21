#include <stdio.h>
#include <unistd.h> // Necesario para usleep

int main() {
    printf("Inicio del programa...\n");

    // Pausa la ejecución durante 1 millón de microsegundos (1 segundo)
    usleep(10000);
    printf("...10ms....\n");

    printf("...fin de la pausa.\n");

    return 0;
}