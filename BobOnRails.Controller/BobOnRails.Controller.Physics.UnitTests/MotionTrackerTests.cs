using System;
using BobOnRails.Controller.Physics.Core;
using NUnit.Framework;

namespace BobOnRails.Controller.Physics.UnitTests
{
    [TestFixture]
    public class MotionTrackerTests
    {
        [TestCase(0.353, 50, 200, 1)]
        [TestCase(1, 50, 1000, 2)]
        [TestCase(1, 50, 100, 2)]
        public void TracksCirclePathProperly(double circleRadius, double timeForOneRotation,
            int timeStepsForOneRotation, int numberOfRotations)
        {
            var angleStep = 2.0 * Math.PI / timeStepsForOneRotation;
            var timeStep = timeForOneRotation / timeStepsForOneRotation;

            //Compute the parameter at the initial point on the circle
            var initialPosition = GetPositionOnCircle(circleRadius, 0);
            var initialVelocity = GetVelocityOnCircle(circleRadius, 0, timeForOneRotation);
            var initialAcceleration = GetAccelerationOnCircle(circleRadius, 0, timeForOneRotation);

            //Initialize the motion tracker
            var initialState = new PathPosition(TimeSpan.Zero, initialPosition, initialVelocity, initialAcceleration);
            var tracker = new MotionTracker(initialState);

            //Move along the circle
            var maxDeviation = 0.0;
            for (int i = 1; i < timeStepsForOneRotation * numberOfRotations; i++)
            {
                var acceleration = GetAccelerationOnCircle(circleRadius, i * angleStep, timeForOneRotation);
                tracker.AppendMotion(acceleration, TimeSpan.FromSeconds(timeStep));

                var currentRadius = tracker.CurrentPosition.Position.Length;
                var deviation = Math.Abs(currentRadius - circleRadius);
                maxDeviation = Math.Max(maxDeviation, deviation);

                Assert.LessOrEqual(deviation, circleRadius * 0.01, $"Motion tracker lost position at step {i}/{timeStepsForOneRotation}");
            }

            TestContext.WriteLine($"Max. deviation was: {maxDeviation}");
        }

        private PositionVector GetPositionOnCircle(double circleRadius, double angle)
        {
            return new PositionVector(
                    Math.Cos(angle) * circleRadius,
                    Math.Sin(angle) * circleRadius,
                    0);
        }

        private VelocityVector GetVelocityOnCircle(double circleRadius, double angle, double timeForOneRotation)
        {
            var angleSpeed = 2.0 * Math.PI / timeForOneRotation;

            return new VelocityVector(
                -Math.Sin(angle) * circleRadius * angleSpeed,
                +Math.Cos(angle) * circleRadius * angleSpeed,
                0);
        }

        private AccelerationVector GetAccelerationOnCircle(double circleRadius, double angle, double timeForOneRotation)
        {
            var angleSpeed = 2.0 * Math.PI / timeForOneRotation;

            return new AccelerationVector(
                -Math.Cos(angle) * circleRadius * angleSpeed * angleSpeed,
                -Math.Sin(angle) * circleRadius * angleSpeed * angleSpeed,
                0);
        }
    }
}
