namespace BobOnRails.Controller
{
    /// <summary>
    /// A struct representing an velocity vector in the cartesian space.
    /// </summary>
    public struct VelocityVector : ICartesianVector
    {
        /// <summary>
        /// Gets or sets the velocity along the x-coordinate [m/s^2].
        /// </summary>
        public double X { get; set; }

        /// <summary>
        /// Gets or sets the velocity along the y-coordinate [m/s^2].
        /// </summary>
        public double Y { get; set; }

        /// <summary>
        /// Gets or sets the velocity along the z-coordinate [m/s^2].
        /// </summary>
        public double Z { get; set; }

        /// <inheritdoc cref="ICartesianVector.Length" />
        public double Length
        {
            get { return CartesianVectorHelper.GetLength(this); }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="VelocityVector"/> class.
        /// </summary>
        /// <param name="x">The velocity along the x-coordinate [m/s].</param>
        /// <param name="y">The velocity along the y-coordinate [m/s].</param>
        /// <param name="z">The velocity along the z-coordinate [m/s].</param>
        public VelocityVector(double x, double y, double z) 
            : this()
        {
            X = x;
            Y = y;
            Z = z;
        }

        public static VelocityVector operator +(VelocityVector a, VelocityVector b)
        {
            return new VelocityVector(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
        }

        public static VelocityVector operator -(VelocityVector a, VelocityVector b)
        {
            return new VelocityVector(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
        }

        public static VelocityVector operator *(VelocityVector position, double scale)
        {
            return new VelocityVector(position.X * scale, position.Y * scale, position.Z * scale);
        }

        public static VelocityVector operator *(double scale, VelocityVector position)
        {
            return new VelocityVector(position.X * scale, position.Y * scale, position.Z * scale);
        }

        /// <inheritdoc />
        public override string ToString()
        {
            return $"{X}, {Y}, {Z}";
        }
    }
}
