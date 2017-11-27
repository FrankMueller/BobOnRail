#include "MotionTracker.h"

namespace BobOnRails::Firmware {
    
    MotionTracker::MotionTracker() {
        
        currentPosition = new PathTarget(0.0, 
			Vector3::zero(), Vector3::zero(), Vector3::zero(),
			Vector3::zero(), Vector3::zero(), Vector3::zero());
    }
    
    MotionTracker::MotionTracker(PathTarget initialState) {
        
        currentPosition = &initialState;
    }
    
    PathTarget MotionTracker::getPosition() {
        return *currentPosition;
    }
    
    void MotionTracker::appendMotion(float timeStep, Vector3 acceleration, Vector3 gyration) {
        
        auto dacc = acceleration - currentPosition->getAcceleration();
        auto velocity = currentPosition->getVelocity() + dacc * timeStep;
        
        auto dvel = velocity - currentPosition->getVelocity();
        auto position = currentPosition->getPosition() + dvel * timeStep;

        auto dgyr = gyration - currentPosition->getGyration();
        auto drift = currentPosition->getDrift() + dgyr * timeStep;
        
        auto dori = drift - currentPosition->getDrift();
        auto orientation = currentPosition->getOrientation() + dori * timeStep;
        
        currentPosition = new PathTarget(currentPosition->getTimeStamp() + timeStep,
            position, velocity, acceleration, 
            orientation, drift, gyration);
    }
}
