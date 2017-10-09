namespace BobOnRails.Controller
{
    /// <summary>
    /// A class representing an acceleration vector in 3D cartesian space.
    /// </summary>
    public sealed class AccelerationVector : ThreeDimensionalVector
    {
        /// <summary>
        /// Gets or sets the acceleration along the x-coordinate [m/s^2].
        /// </summary>
        public override double X { get => base.X; set => base.X = value; }

        /// <summary>
        /// Gets or sets the acceleration along the y-coordinate [m/s^2].
        /// </summary>
        public override double Y { get => base.Y; set => base.Y = value; }

        /// <summary>
        /// Gets or sets the acceleration along the z-coordinate [m/s^2].
        /// </summary>
        public override double Z { get => base.Z; set => base.Z = value; }

        /// <summary>
        /// Initializes a new instance of the <see cref="AccelerationVector"/> class.
        /// </summary>
        /// <param name="x">The acceleration along the x-coordinate [m/s^2].</param>
        /// <param name="y">The acceleration along the y-coordinate [m/s^2].</param>
        /// <param name="z">The acceleration along the z-coordinate [m/s^2].</param>
        public AccelerationVector(double x, double y, double z)
            : base(x, y, z)
        { }

        public static AccelerationVector operator +(AccelerationVector a, AccelerationVector b)
        {
            return new AccelerationVector(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
        }

        public static AccelerationVector operator -(AccelerationVector a, AccelerationVector b)
        {
            return new AccelerationVector(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
        }

        public static AccelerationVector operator *(AccelerationVector position, double scale)
        {
            return new AccelerationVector(position.X * scale, position.Y * scale, position.Z * scale);
        }

        public static AccelerationVector operator *(double scale, AccelerationVector position)
        {
            return new AccelerationVector(position.X * scale, position.Y * scale, position.Z * scale);
        }
    }
}
