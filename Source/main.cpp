#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include "Vector3.h"
#include "GyroSensorMPU6050.h"
#include "MotionTracker.h"

int main(int argc, char *argv[])
{
	auto sensor = BobOnRails::Firmware::GyroSensorMPU6050();
	sensor.connect();

	auto tracker = BobOnRails::Firmware::MotionTracker();

	int sampleTime = 1000000; //The sample time in micro seconds


	timeval now, lastMeasurementStartTime;

	gettimeofday(&lastMeasurementStartTime, NULL);
	do
	{
		timeval measurementStartTime;
		gettimeofday(&measurementStartTime, NULL);

		auto temperature = 0.0f;
		auto acceleration = BobOnRails::Firmware::Vector3();
		auto gyration = BobOnRails::Firmware::Vector3();
		sensor.measure(&acceleration, &gyration, &temperature);

		printf("Acceleration: (%f, %f, %f)[m/s^2], (%f, %f, %f)[deg/s^2], (%f)[°C]\n",
			acceleration.X, acceleration.Y, acceleration.Z,
			gyration.X, gyration.Y, gyration.Z,
			temperature);

		auto timeBetweenMeasurements =
			(lastMeasurementStartTime.tv_usec - measurementStartTime.tv_usec) * 1E-6;
		tracker.appendMotion(timeBetweenMeasurements, acceleration, gyration);

		gettimeofday(&now, NULL);
		auto usedCycleTime = now.tv_usec - measurementStartTime.tv_usec;

		auto currentPosition = tracker.getPosition();
		printf("Position: (%f, %f, %f)[m]\n", currentPosition);

		auto sleepTime = sampleTime - usedCycleTime;
		printf("Cycle time was %d micros seconds, sleeping for %d micro seconds\n", usedCycleTime, sleepTime);
		usleep(sleepTime);

		lastMeasurementStartTime = measurementStartTime;
	} while (1);
}
