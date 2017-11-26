#include "MotionTracker.h"

namespace BobOnRails::Firmware {
    
    MotionTracker::MotionTracker() {
        
        currentPosition = PathTarget(0f, Vector3.Zero, Vector3.Zero, Vector3.Zero);

        this.position = position;
        this.velocity = velocity;
        this.acceleration = acceleration;
    
        this.orientation = orientation;
        this.drift = drift;
        this.gyration = gyration;
    }
    
    MotionTracker::MotionTracker(PathTarget initialState) {
        
        currentPosition = initialState;
    }
    
    PathTarget MotionTracker::getPosition() {
        return currentPosition;
    }
    
    void MotionTracker::AppendMotion(float timeStep, Vector3 acceleration, Vector3 gyration) {
        
        auto dacc = acceleration - currentPosition.acceleration;
        auto velocity = currentPosition.velocity + dacc * timeStep;
        
        auto dvel = velocity - currentPosition.velocity;
        auto position = currentPosition.position + dvel * timeStep;

        auto dgyr = gyration - currentPosition.gyration;
        auto drift = currentPosition.drift + dgyr * timeStep;
        
        auto dori = drift - currentPosition.drift;
        auto orientation = currentPosition.orientation + dori * timeStep;
        
        currentPosition = PathTarget(currentPosition.getTimeStamp() + timeStep,
            position, velocity, acceleration, 
            orientation, drift, gyration);
    }
}