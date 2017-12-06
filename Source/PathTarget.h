// Copyright 2017 Frank Mueller
#ifndef SOURCE_PATHTARGET_H_
#define SOURCE_PATHTARGET_H_

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
}       // namespace Firmware
}       // namespace BobOnRails
#endif  // SOURCE_PATHTARGET_H_
