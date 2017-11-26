#include <unistd.h>
#include <sys/time.h>
#include "Vector3.h"
#include "GyroSensorMPU6050.h"
#include "MotionTracker.h"

int main(int argc, char *argv[])
{
    BobOnRails::Firmware::GyroSensorMPU6050 sensor;
    sensor.connect();

    BobOnRails::Firmware::MotionTracker tracker;
    
    int sampleTime = 1000; //The sample time in micro seconds
    
    float temperature;
    BobOnRails::Firmware::Vector3 acceleration, gyration;
    
    timeval now, measurementStartTime, lastMeasurementStartTime;
    gettimeofday(&lastMeasurementStartTime, NULL);
    do
    {
        gettimeofday(&measurementStartTime, NULL);
        sensor.measure(&acceleration, &gyration, &temperature);

        printf("Acceleration: (%f, %f, %f)[m/s^2], (%f, %f, %f)[deg/s^2], (%f)[°C]\n", 
            acceleration.X, acceleration.Y, acceleration.Z,
            gyration.X, gyration.Y, gyration.Z,
            temperature);
    
        auto timeBetweenMeasurements = 
            (lastMeasurementStartTime.tv_usec - measurementStartTime.tv_usec) * 1E6;
        tracker.appendMotion(timeBetweenMeasurements, acceleration, gyration);
        
        gettimeofday(&now, NULL);
        auto usedCycleTime = now.tv_usec - measurementStartTime.tv_usec;
    
        auto currentPosition = tracker.getPosition();
        printf("Position: (%f, %f, %f)[m]", currentPosition);
    
        usleep(sampleTime - usedCycleTime);
        lastMeasurementStartTime = measurementStartTime;
    }
    while (1);
}

