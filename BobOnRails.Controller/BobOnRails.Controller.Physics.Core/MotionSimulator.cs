using System;

namespace BobOnRails.Controller.Physics.Core
{
    public static class MotionSimulator
    {
        public static Path GetConstantSpeedCirclePath(double circleRadius, double speed,
            double sampleFrequency, double rotations = 1)
        {
            var timeForOneRotation = Math.PI * circleRadius / speed;
            var timeStepsForOneRotation = timeForOneRotation * sampleFrequency;

            var timeStep = 1.0 / sampleFrequency;
            var angleStep = 2.0 * Math.PI / timeStepsForOneRotation;

            var path = new Path();
            for (int i = 0; i < timeStepsForOneRotation * rotations; i++)
            {
                var angle = angleStep * i;
                path.Add(new PathPosition(
                    TimeSpan.FromSeconds(timeStep * i),
                    GetPositionOnCircle(circleRadius, angle),
                    GetVelocityOnCircle(circleRadius, angle, timeForOneRotation),
                    GetAccelerationOnCircle(circleRadius, angle, timeForOneRotation)));
            }

            return path;
        }

        private static PositionVector GetPositionOnCircle(double circleRadius, double angle)
        {
            return new PositionVector(
                    Math.Cos(angle) * circleRadius,
                    Math.Sin(angle) * circleRadius,
                    0);
        }

        private static VelocityVector GetVelocityOnCircle(double circleRadius, double angle, double timeForOneRotation)
        {
            var angleSpeed = 2.0 * Math.PI / timeForOneRotation;

            return new VelocityVector(
                -Math.Sin(angle) * circleRadius * angleSpeed,
                +Math.Cos(angle) * circleRadius * angleSpeed,
                0);
        }

        private static AccelerationVector GetAccelerationOnCircle(double circleRadius, double angle, double timeForOneRotation)
        {
            var angleSpeed = 2.0 * Math.PI / timeForOneRotation;

            return new AccelerationVector(
                -Math.Cos(angle) * circleRadius * angleSpeed * angleSpeed,
                -Math.Sin(angle) * circleRadius * angleSpeed * angleSpeed,
                0);
        }
    }
}
