namespace BobOnRails.Controller
{
    /// <summary>
    /// A class representing an velocity vector in 3D cartesian space.
    /// </summary>
    public class VelocityVector : ThreeDimensionalVector
    {
        /// <summary>
        /// Gets or sets the velocity along the x-coordinate [m/s^2].
        /// </summary>
        public override double X { get => base.X; set => base.X = value; }

        /// <summary>
        /// Gets or sets the velocity along the y-coordinate [m/s^2].
        /// </summary>
        public override double Y { get => base.Y; set => base.Y = value; }

        /// <summary>
        /// Gets or sets the velocity along the z-coordinate [m/s^2].
        /// </summary>
        public override double Z { get => base.Z; set => base.Z = value; }

        /// <summary>
        /// Initializes a new instance of the <see cref="VelocityVector"/> class.
        /// </summary>
        /// <param name="x">The velocity along the x-coordinate [m/s].</param>
        /// <param name="y">The velocity along the y-coordinate [m/s].</param>
        /// <param name="z">The velocity along the z-coordinate [m/s].</param>
        public VelocityVector(double x, double y, double z) 
            : base(x, y, z)
        { }

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
    }
}
