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
            var speed = Math.PI * circleRadius / timeForOneRotation;
            var sampleFrequency = timeStepsForOneRotation / timeForOneRotation;
            var path = MotionSimulator.GetConstantSpeedCirclePath(circleRadius, speed, sampleFrequency, numberOfRotations);

            //Initialize the motion tracker
            var tracker = new MotionTracker(path[0]);

            //Move along the circle
            var maxDeviation = 0.0;
            for (int i = 1; i < path.Count; i++)
            {
                var pathPoint = path[i];
                var previousPathPoint = path[i - 1];
                tracker.AppendMotion(pathPoint.Acceleration, pathPoint.Time - previousPathPoint.Time);

                var currentRadius = tracker.CurrentPosition.Position.Length;
                var deviation = Math.Abs(currentRadius - circleRadius);
                maxDeviation = Math.Max(maxDeviation, deviation);

                Assert.LessOrEqual(deviation, circleRadius * 0.01, $"Motion tracker lost position at step {i}/{timeStepsForOneRotation}");
            }

            TestContext.WriteLine($"Max. deviation was: {maxDeviation}");
        }
    }
}
