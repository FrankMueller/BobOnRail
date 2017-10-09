namespace BobOnRails.Controller
{
    /// <summary>
    /// A class representing a position in 3D cartesian space.
    /// </summary>
    public class PositionVector : ThreeDimensionalVector
    {
        /// <summary>
        /// Gets or sets the x-coordinate of the position [m].
        /// </summary>
        public override double X { get => base.X; set => base.X = value; }

        /// <summary>
        /// Gets or sets the y-coordinate of the position [m].
        /// </summary>
        public override double Y { get => base.Y; set => base.Y = value; }

        /// <summary>
        /// Gets or sets the z-coordinate of the position [m].
        /// </summary>
        public override double Z { get => base.Z; set => base.Z = value; }

        /// <summary>
        /// Initializes a new instance of the <see cref="PositionVector"/> class.
        /// </summary>
        /// <param name="x">The x-coordinate of the position [m].</param>
        /// <param name="y">The y-coordinate of the position [m].</param>
        /// <param name="z">The z-coordinate of the position [m].</param>
        public PositionVector(double x, double y, double z) 
            : base(x, y, z)
        { }

        public static PositionVector operator +(PositionVector a, PositionVector b)
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
    }
}
