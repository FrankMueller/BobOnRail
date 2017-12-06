// Copyright 2017 Frank Mueller
#ifndef SOURCE_VECTOR3_H_
#define SOURCE_VECTOR3_H_

namespace BobOnRails {
namespace Firmware {

class Vector3 {
 public:
    double X;
    double Y;
    double Z;

    /**
       Initializes a new instance of the Vector3 class.
      */
    Vector3();

    /**
       Initializes a new instance of the Vector3 class.

       @param[in]  x The x-coordinate of the vector.
       @param[in]  y The y-coordinate of the vector.
       @param[in]  z The z-coordinate of the vector.
      */
    Vector3(double x, double y, double z);

    /**
       Gets the length of the vector.

       @return The length.
     */
    double length() const;

    /**
       Gets a new vector with all coordinates set to zero.

       @return The vector.
     */
    static Vector3 zero();

    /**
       Gets a new vector with a length of one, pointing in x-direction.

       @return The vector.
     */
    static Vector3 vx();

    /**
       Gets a new vector with a length of one, pointing in y-direction.

       @return The vector.
     */
    static Vector3 vy();

    /**
       Gets a new vector with a length of one, pointing in z-direction.

       @return The vector.
     */
    static Vector3 vz();

    /**
       Gets a new vector representing the sum of the two specified
       vectors.

       @param[in] v1 the first summand.
       @param[in] v2 the second summand.

       @return The sum vector.
     */
    static Vector3 add(Vector3 v1, Vector3 v2);

    static Vector3 subtract(Vector3 v1, Vector3 v2);

    static Vector3 scale(Vector3 v, double scale);

    Vector3 operator+(Vector3 v) const;

    Vector3 operator-(Vector3 v) const;

    Vector3 operator-() const;

    Vector3 operator*(double factor) const;
};
}       // namespace Firmware
}       // namespace BobOnRails
#endif  // SOURCE_VECTOR3_H_
