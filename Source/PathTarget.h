#ifndef BobOnRails_Firmware_PathTarget_H
#define BobOnRails_Firmware_PathTarget_H

namespace BobOnRails {
	namespace Firmware {

		class PathTarget {

		public:
			PathTarget();

			PathTarget(double timeStamp,
				Vector3 position, Vector3 velocity, Vector3 acceleration,
				Vector3 orientation, Vector3 drift, Vector3 gyration);

			double getTimeStamp();

			Vector3 getPosition();

			Vector3 getVelocity();

			Vector3 getAcceleration();

			Vector3 getOrientation();

			Vector3 getDrift();

			Vector3 getGyration();

		private:
			double timeStamp;

			Vector3 position;
			Vector3 velocity;
			Vector3 acceleration;

			Vector3 orientation;
			Vector3 drift;
			Vector3 gyration;
		};
	}
}
#endif
