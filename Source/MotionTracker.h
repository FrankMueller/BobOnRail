#ifndef BobOnRails_Firmware_MotionTracker_H
#define BobOnRails_Firmware_MotionTracker_H

#include "Vector3.h"
#include "PathTarget.h"

namespace BobOnRails {
	namespace Firmware {

		class MotionTracker {

		public:
			MotionTracker();

			MotionTracker(PathTarget initialState);

			PathTarget getPosition();

			void appendMotion(double timeStep, Vector3 acceleration, Vector3 gyration);

		private:
			PathTarget currentPosition;
		};
	}
}
#endif
