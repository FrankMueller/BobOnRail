#include "Vector3.h"
#include "PathTarget.h"

namespace BobOnRails::Firmware {
    
    PathTarget::PathTarget(float timeStamp, 
        Vector3 position, Vector3 velocity, Vector3 acceleration,
        Vector3 orientation, Vector3 drift, Vector3 gyration) {
        
        this.timeStamp = timeStamp;

        this.position = position;
        this.velocity = velocity;
        this.acceleration = acceleration;
    
        this.orientation = orientation;
        this.drift = drift;
        this.gyration = gyration;
    }
    
    float PathTarget::getTimeStamp() {
        return timeStamp;
    }

    Vector3 PathTarget::getPosition() {
        return position;
    }
    
    Vector3 PathTarget::getVelocity() {
        return velocity;
    }
    
    Vector3 PathTarget::getAcceleration() {
        return acceleration;
    }
    
    Vector3 PathTarget::getOrientation() {
        return orientation;
    }
    
    Vector3 PathTarget::getDrift() {
        return drift;
    }
    
    Vector3 PathTarget::getGyration() {
        return gyration;
    }
}