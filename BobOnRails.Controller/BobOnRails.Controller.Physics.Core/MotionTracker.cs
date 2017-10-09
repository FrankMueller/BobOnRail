using System;
using System.Collections.ObjectModel;
using System.Linq;

namespace BobOnRails.Controller.Physics.Core
{
    /// <summary>
    /// A motion tracker which tracks the position of an object by integrating
    /// acceleration measures.
    /// </summary>
    public class MotionTracker
    {
        private Path path;

        /// <summary>
        /// Gets the path the object moves along.
        /// </summary>
        public ReadOnlyCollection<PathPosition> Path { get; private set; }

        /// <summary>
        /// Gets the current (last) position on the <see cref="Path"/>.
        /// </summary>
        public PathPosition CurrentPosition
        {
            get { return path.Last(); }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="MotionTracker"/> class.
        /// </summary>
        public MotionTracker()
            : this(new PathPosition())
        { }

        public MotionTracker(PathPosition initialPosition)
        {
            path = new Path();
            path.Add(initialPosition);

            Path = path.AsReadOnly();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="acceleration"></param>
        /// <param name="timeStep"></param>
        public void AppendMotion(AccelerationVector acceleration, TimeSpan timeStep)
        {
            var currentPosition = CurrentPosition;

            var newPosition = new PathPosition();
            newPosition.Time = currentPosition.Time.Add(timeStep);
            newPosition.Acceleration = acceleration;

            var averageAcceleration = (currentPosition.Acceleration + newPosition.Acceleration) * 0.5;
            newPosition.Velocity = currentPosition.Velocity + MotionCalculator.GetVelocityChange(averageAcceleration, timeStep);

            var averageVelocity = (currentPosition.Velocity + newPosition.Velocity) * 0.5;
            newPosition.Position = currentPosition.Position + MotionCalculator.GetPositionChange(averageVelocity, timeStep);

            path.Add(newPosition);
        }
    }
}
