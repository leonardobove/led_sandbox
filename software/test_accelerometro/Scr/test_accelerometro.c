#include "../Inc/config.h"

int main() {
    // Puntatore alla periferica accelerometro
    alt_up_accelerometer_spi_dev *accel_dev;

    // Apri il device accelerometro specificato in system.h
    accel_dev = alt_up_accelerometer_spi_open_dev("/dev/accelerometer_spi_0");
    if (accel_dev == NULL) {
        printf("Errore: impossibile aprire il dispositivo accelerometro.\n");
        return 1;
    }

    printf("Accelerometro inizializzato con successo.\n");

    // Variabili per immagazzinare i valori di X, Y e Z
    int x, y, z;

    while (1) {
        // Leggi i valori dei tre assi
        alt_up_accelerometer_spi_read_x_axis(accel_dev, &x);
        alt_up_accelerometer_spi_read_y_axis(accel_dev, &y);
        alt_up_accelerometer_spi_read_z_axis(accel_dev, &z);

        // Stampa i valori
        //if(x!=0 || y!=0 || z!=0){
        printf("X: %d\tY: %d\tZ: %d\n", x, y, z);
    	//}
        // Attendi 100 millisecondi
        usleep(100000);
    }

}







