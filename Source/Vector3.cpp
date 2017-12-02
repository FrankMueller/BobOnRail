#include "math.h"
#include "Vector3.h"

namespace BobOnRails {
	namespace Firmware {

		Vector3::Vector3() {
		}

		Vector3::Vector3(double x, double y, double z) {
			X = x;
			Y = y;
			Z = z;
		}

		double Vector3::length() const {
			return sqrt(X * X + Y * Y + Z * Z);
		}

		Vector3 Vector3::zero() {
			return Vector3(0, 0, 0);
		}

		Vector3 Vector3::vx() {
			return Vector3(1, 0, 0);
		}

		Vector3 Vector3::vy() {
			return Vector3(0, 1, 0);
		}

		Vector3 Vector3::vz() {
			return Vector3(0, 0, 1);
		}

		Vector3 Vector3::add(Vector3 v1, Vector3 v2) {
			return v1 + v2;
		}

		Vector3 Vector3::subtract(Vector3 v1, Vector3 v2) {
			return v1 - v2;
		}

		Vector3 Vector3::scale(Vector3 v, double scale) {
			return v * scale;
		}

		Vector3 Vector3::operator+(Vector3 v) const {
			Vector3 sum;
			sum.X = X + v.X;
			sum.Y = Y + v.Y;
			sum.Z = Z + v.Z;

			return sum;
		}

		Vector3 Vector3::operator-(Vector3 v) const {
			Vector3 difference;
			difference.X = X - v.X;
			difference.Y = Y - v.Y;
			difference.Z = Z - v.Z;

			return difference;
		}

		Vector3 Vector3::operator-() const {
			Vector3 inverse;
			inverse.X = -X;
			inverse.Y = -Y;
			inverse.Z = -Z;

			return inverse;
		}

		Vector3 Vector3::operator*(double factor) const {
			Vector3 res;
			res.X = X * factor;
			res.Y = Y * factor;
			res.Z = Z * factor;

			return res;
		}
	}
}