#include <unistd.h>
#include "MPU6050.h"
#include "MPU6050.c"

int main(int argc, char *argv[])
{
    connectMPU6050();

    float temperature;
    float accelerationInX, accelerationInY, accelerationInZ;
    float gyrationInX, gyrationInY, gyrationInZ;
    do
    {
        measure(&accelerationInX, &accelerationInY, &accelerationInZ,
                &gyrationInX, &gyrationInY, &gyrationInZ,
                &temperature);

        printf("Acceleration x,y,z: %f, %f, %f\n", 
            accelerationInX, accelerationInY, accelerationInZ);
    
        printf("Temperature: %f [°]\n", temperature);
    
        printf("Gyration x,y,z: %f, %f, %f\n", 
            gyrationInX, gyrationInY, gyrationInZ);

        usleep(100000);
    }
    while (1);
}

