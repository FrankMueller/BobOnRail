// Copyright 2017 Frank Mueller
#ifndef SOURCE_MOTIONTRACKER_H_
#define SOURCE_MOTIONTRACKER_H_

#include "Vector3.h"
#include "PathTarget.h"

namespace BobOnRails {
namespace Firmware {

class MotionTracker {
 public:
    MotionTracker();

    explicit MotionTracker(PathTarget initialState);

    PathTarget getPosition();

    void appendMotion(double timeStep, Vector3 acceleration, Vector3 gyration);

 private:
    PathTarget currentPosition;
};
}       // namespace Firmware
}       // namespace BobOnRails
#endif  // SOURCE_MOTIONTRACKER_H_
