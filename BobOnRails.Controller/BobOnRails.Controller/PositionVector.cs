namespace BobOnRails.Controller
{
    /// <summary>
    /// A struct representing a position in the cartesian space.
    /// </summary>
    public struct PositionVector : ICartesianVector
    {
        /// <summary>
        /// Gets or sets the x-coordinate of the position [m].
        /// </summary>
        public double X { get; set; }

        /// <summary>
        /// Gets or sets the y-coordinate of the position [m].
        /// </summary>
        public double Y { get; set; }

        /// <summary>
        /// Gets or sets the z-coordinate of the position [m].
        /// </summary>
        public double Z { get; set; }

        /// <inheritdoc cref="ICartesianVector.Length" />
        public double Length
        {
            get { return CartesianVectorHelper.GetLength(this); }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="PositionVector"/> class.
        /// </summary>
        /// <param name="x">The x-coordinate of the position [m].</param>
        /// <param name="y">The y-coordinate of the position [m].</param>
        /// <param name="z">The z-coordinate of the position [m].</param>
        public PositionVector(double x, double y, double z) 
            : this()
        {
            X = x;
            Y = y;
            Z = z;
        }

        public static PositionVector operator+(PositionVector a, PositionVector b)
        {
            return new PositionVector(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
        }

        public static PositionVector operator -(PositionVector a, PositionVector b)
        {
            return new PositionVector(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
        }

        public static PositionVector operator *(PositionVector position, double scale)
        {
            return new PositionVector(position.X * scale, position.Y * scale, position.Z * scale);
        }

        public static PositionVector operator *(double scale, PositionVector position)
        {
            return new PositionVector(position.X * scale, position.Y * scale, position.Z * scale);
        }

        /// <inheritdoc />
        public override string ToString()
        {
            return $"{X}, {Y}, {Z}";
        }
    }
}
