using System;

namespace BobOnRails.Controller
{
    public static class CartesianVectorHelper
    {
        public static double GetLength(ICartesianVector vector)
        {
            return Math.Sqrt(vector.X * vector.X + vector.Y * vector.Y + vector.Z * vector.Z);
        }
    }
}
