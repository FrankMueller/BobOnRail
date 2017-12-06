// Copyright 2017 Frank Mueller
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include "Vector3.h"
#include "GyroSensorMPU6050.h"
#include "MotionTracker.h"

int main(int argc, char *argv[]) {
    auto sensor = BobOnRails::Firmware::GyroSensorMPU6050();
    sensor.connect();

    auto tracker = BobOnRails::Firmware::MotionTracker();

    int sampleTime = 1000000;   // The sample time in micro seconds

    timeval now, lastMeasurementStartTime;

    gettimeofday(&lastMeasurementStartTime, NULL);
    do {
        timeval measurementStartTime;
        gettimeofday(&measurementStartTime, NULL);

        auto temperature = 0.0f;
        auto acceleration = BobOnRails::Firmware::Vector3();
        auto gyration = BobOnRails::Firmware::Vector3();
        sensor.measure(&acceleration, &gyration, &temperature);

        auto timeBetweenMeasurements =
            (lastMeasurementStartTime.tv_usec - measurementStartTime.tv_usec) * 1E-6;
        tracker.appendMotion(timeBetweenMeasurements, acceleration, gyration);

        gettimeofday(&now, NULL);
        auto usedCycleTime = now.tv_usec - measurementStartTime.tv_usec;

        auto currentPosition = tracker.getPosition().getPosition();

        auto sleepTime = sampleTime - usedCycleTime;

        printf("\rState: a=(%5.2f, %5.2f, %5.2f)[m/s^2], g=(%5.2f, %5.2f, %5.2f)[deg/s^2],"
            "T=(%5.2f)[°C], P=(%7.4f, %7.4f, %7.4f)[m], dt=(%5.2f)[ms]",
            acceleration.X, acceleration.Y, acceleration.Z,
            gyration.X, gyration.Y, gyration.Z,
            temperature,
            currentPosition.X, currentPosition.Y, currentPosition.Z,
            usedCycleTime * 0.001);

        usleep(sleepTime);

        lastMeasurementStartTime = measurementStartTime;
    } while (1);
}
