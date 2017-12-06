// Copyright 2017 Frank Mueller
#include "MotionTracker.h"

namespace BobOnRails {
namespace Firmware {

MotionTracker::MotionTracker() {
    currentPosition = PathTarget();
}

MotionTracker::MotionTracker(PathTarget initialState) {
    currentPosition = initialState;
}

PathTarget MotionTracker::getPosition() {
    return currentPosition;
}

void MotionTracker::appendMotion(double timeStep, Vector3 acceleration, Vector3 gyration) {
    auto dacc = acceleration - currentPosition.getAcceleration();
    auto velocity = currentPosition.getVelocity() + dacc * timeStep;

    auto dvel = velocity - currentPosition.getVelocity();
    auto position = currentPosition.getPosition() + dvel * timeStep;

    auto dgyr = gyration - currentPosition.getGyration();
    auto drift = currentPosition.getDrift() + dgyr * timeStep;

    auto dori = drift - currentPosition.getDrift();
    auto orientation = currentPosition.getOrientation() + dori * timeStep;

    currentPosition = PathTarget(currentPosition.getTimeStamp() + timeStep,
        position, velocity, acceleration,
        orientation, drift, gyration);
}
}       // namespace Firmware
}       // namespace BobOnRails
