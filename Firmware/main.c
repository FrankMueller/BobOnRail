#include "MPU6050.h"
#include "MPU6050.c"


#define A_GAIN 0.0573      // [deg/LSB]
#define G_GAIN 0.070     // [deg/s/LSB]
#define RAD_TO_DEG 57.29578
#define M_PI 3.14159265358979323846


int main(int argc, char *argv[])
{
    setup();

	loop();
}

