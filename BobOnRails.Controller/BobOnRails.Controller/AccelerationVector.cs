namespace BobOnRails.Controller
{
    /// <summary>
    /// A struct representing an acceleration vector in the cartesian space.
    /// </summary>
    public struct AccelerationVector : ICartesianVector
    {
        /// <summary>
        /// Gets or sets the acceleration along the x-coordinate [m/s^2].
        /// </summary>
        public double X { get; set; }

        /// <summary>
        /// Gets or sets the acceleration along the y-coordinate [m/s^2].
        /// </summary>
        public double Y { get; set; }

        /// <summary>
        /// Gets or sets the acceleration along the z-coordinate [m/s^2].
        /// </summary>
        public double Z { get; set; }

        /// <inheritdoc cref="ICartesianVector.Length" />
        public double Length
        {
            get { return CartesianVectorHelper.GetLength(this); }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="AccelerationVector"/> class.
        /// </summary>
        /// <param name="x">The acceleration along the x-coordinate [m/s^2].</param>
        /// <param name="y">The acceleration along the y-coordinate [m/s^2].</param>
        /// <param name="z">The acceleration along the z-coordinate [m/s^2].</param>
        public AccelerationVector(double x, double y, double z) 
            : this()
        {
            X = x;
            Y = y;
            Z = z;
        }

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

        /// <inheritdoc />
        public override string ToString()
        {
            return $"{X}, {Y}, {Z}";
        }
    }
}
