using System;

namespace BobOnRails.Controller
{
    /// <summary>
    /// A basic implementation for a vector in 3D cartesian space.
    /// </summary>
    public abstract class ThreeDimensionalVector
    {
        /// <summary>
        /// Gets or sets the x-coordinate of the vector.
        /// </summary>
        public virtual double X { get; set; }

        /// <summary>
        /// Gets or sets the y-coordinate of the vector.
        /// </summary>
        public virtual double Y { get; set; }

        /// <summary>
        /// Gets or sets the z-coordinate of the vector.
        /// </summary>
        public virtual double Z { get; set; }

        /// <summary>
        /// Gets the length of the vector.
        /// </summary>
        public double Length
        {
            get
            {
                return Math.Sqrt(X * X + Y * Y + Z * Z);
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="ThreeDimensionalVector"/> class.
        /// </summary>
        public ThreeDimensionalVector()
        { }

        /// <summary>
        /// Initializes a new instance of the <see cref="ThreeDimensionalVector"/> class.
        /// </summary>
        /// <param name="x">The x-coordinate of the vector.</param>
        /// <param name="y">The y-coordinate of the vector.</param>
        /// <param name="z">The z-coordinate of the vector.</param>
        public ThreeDimensionalVector(double x, double y, double z) 
            : this()
        {
            X = x;
            Y = y;
            Z = z;
        }

        /// <inheritdoc />
        public override string ToString()
        {
            return $"{X}, {Y}, {Z}";
        }
    }
}
