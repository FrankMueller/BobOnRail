using System;

namespace BobOnRails.Controller
{
    /// <summary>
    /// Represents a position on the path of Bob.
    /// </summary>
    public class PathPosition
    {
        public TimeSpan TimeStep { get; set; }

        public PositionVector Position { get; set; }

        public VelocityVector Velocity { get; set; }

        public AccelerationVector Acceleration { get; set; }

        public PathPosition()
        { }

        public PathPosition(TimeSpan timeStep, PositionVector position, VelocityVector velocity, AccelerationVector acceleration)
            : this()
        {
            TimeStep = timeStep;
            Position = position;
            Velocity = velocity;
            Acceleration = acceleration;
        }
    }
}
