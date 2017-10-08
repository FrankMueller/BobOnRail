using System;
using BobOnRails.Controller.Physics.Core;
using NUnit.Framework;

namespace BobOnRails.Controller.Physics.UnitTests
{
    [TestFixture]
    public class MotionTrackerTests
    {
        [TestCase(1, 50, 1000, 2)]
        [TestCase(1, 50, 100, 2)]
        public void TracksCirclePathProperly(double circleRadius, double timeForOneRotation,
            int timeStepsForOneRotation, int numberOfRotations)
        {
            var angleStep = 2.0 * Math.PI / timeStepsForOneRotation;
            var timeStep = timeForOneRotation / timeStepsForOneRotation;

            //Compute the parameter at the initial point on the circle
            var initialPosition = new PositionVector(
                Math.Cos(0) * circleRadius, 
                Math.Sin(0) * circleRadius, 
                0);

            var initialVelocity = new VelocityVector(
                0,
                2.0 * Math.PI * circleRadius / timeForOneRotation,
                0);

            var initialAcceleration = new AccelerationVector(
                0,
                0,
                0);

            //Initialize the motion tracker
            var tracker = new MotionTracker(
                new PathPosition(TimeSpan.Zero, initialPosition, initialVelocity, initialAcceleration));

            //Move along the circle
            var lastPosition = initialPosition;
            var lastVelocity = initialVelocity;
            var maxDeviation = 0.0;
            for (int i = 1; i < timeStepsForOneRotation * numberOfRotations; i++)
            {
                var angle = i * angleStep;

                var position = new PositionVector(
                    Math.Cos(angle) * circleRadius,
                    Math.Sin(angle) * circleRadius,
                    0);

                var velocity = new VelocityVector(
                    (position.X - lastPosition.X) / timeStep,
                    (position.Y - lastPosition.Y) / timeStep,
                    (position.Z - lastPosition.Z) / timeStep);

                var acceleration = new AccelerationVector(
                    (velocity.X - lastVelocity.X) / timeStep,
                    (velocity.Y - lastVelocity.Y) / timeStep,
                    (velocity.Z - lastVelocity.Z) / timeStep);

                lastPosition = position;
                lastVelocity = velocity;

                tracker.AppendMotion(acceleration, TimeSpan.FromSeconds(timeStep));

                var currentPosition = tracker.CurrentPosition.Position;
                var currentRadius = Math.Sqrt(currentPosition.X * currentPosition.X + currentPosition.Y * currentPosition.Y);
                var deviation = Math.Abs(currentRadius - circleRadius);
                maxDeviation = Math.Max(maxDeviation, deviation);

                Assert.LessOrEqual(deviation, circleRadius * 0.01, $"Motion tracker lost position at step {i}/{timeStepsForOneRotation}");
            }

            TestContext.WriteLine($"Max. deviation was: {maxDeviation}");
        }
    }
}
