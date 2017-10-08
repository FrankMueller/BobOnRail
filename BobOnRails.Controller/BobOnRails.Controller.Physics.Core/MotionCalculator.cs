using System;

namespace BobOnRails.Controller.Physics.Core
{
    public static class MotionCalculator
    {
        /// <summary>
        /// Computes the change in position from the specified velocity
        /// and time span.
        /// </summary>
        /// <param name="velocity">The velocity (v) [m/s].</param>
        /// <param name="timeStep">The time span (dt).</param>
        /// <returns>The change in position dp = (v*dt) [m].</returns>
        public static PositionVector GetPositionChange(VelocityVector veloctiy, TimeSpan timeStep)
        {
            return GetPositionChange(veloctiy, timeStep.TotalSeconds);
        }

        /// <summary>
        /// Computes the change in position from the specified velocity
        /// and time span.
        /// </summary>
        /// <param name="velocity">The velocity (v) [m/s].</param>
        /// <param name="timeStep">The time span (dt) [s].</param>
        /// <returns>The change in position dp = (v*dt) [m].</returns>
        public static PositionVector GetPositionChange(VelocityVector veloctiy, double timeStep)
        {
            return new PositionVector(GetPositionChange(veloctiy.X, timeStep),
                                GetPositionChange(veloctiy.Y, timeStep),
                                GetPositionChange(veloctiy.Z, timeStep));
        }

        /// <summary>
        /// Computes the change in velocity from the specified acceleration
        /// and time span.
        /// </summary>
        /// <param name="acceleration">The acceleration (a) [m/s^2].</param>
        /// <param name="timeStep">The time span.</param>
        /// <returns>The change in velocity dv = (a*dt) [m/s].</returns>
        public static VelocityVector GetVelocityChange(AccelerationVector acceleration, TimeSpan timeStep)
        {
            return GetVelocityChange(acceleration, timeStep.TotalSeconds);
        }

        /// <summary>
        /// Computes the change in velocity from the specified acceleration
        /// and time span.
        /// </summary>
        /// <param name="acceleration">The acceleration (a) [m/s^2].</param>
        /// <param name="timeStep">The time span (dt) [s].</param>
        /// <returns>The change in velocity dv = (a*dt) [m/s].</returns>
        public static VelocityVector GetVelocityChange(AccelerationVector acceleration, double timeStep)
        {
            return new VelocityVector(GetVelocityChange(acceleration.X, timeStep),
                                      GetVelocityChange(acceleration.Y, timeStep),
                                      GetVelocityChange(acceleration.Z, timeStep));
        }

        /// <summary>
        /// Computes the change in position from the specified velocity
        /// and time span.
        /// </summary>
        /// <param name="velocity">The velocity (v) [m/s].</param>
        /// <param name="timeStep">The time span (dt) [s].</param>
        /// <returns>The change in position dp = (v*dt) [m].</returns>
        public static double GetPositionChange(double velocity, double timeStep)
        {
            return velocity * timeStep;
        }

        /// <summary>
        /// Computes the change in velocity from the specified acceleration
        /// and time span.
        /// </summary>
        /// <param name="acceleration">The acceleration (a) [m/s^2].</param>
        /// <param name="timeStep">The time span (dt) [s].</param>
        /// <returns>The change in velocity dv = (a*dt) [m/s].</returns>
        public static double GetVelocityChange(double acceleration, double timeStep)
        {
            return acceleration * timeStep;
        }
    }
}
