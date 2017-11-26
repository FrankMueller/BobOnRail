#ifndef BobOnRails_Firmware_MotionTracker_H
#define BobOnRails_Firmware_MotionTracker_H

#include "Vector3.h"
#include "PathTarget.h"

namespace BobOnRails::Firmware {
    
    class MotionTracker {
        
        public:
            MotionTracker();
            
            MotionTracker(PathTarget);
            
            PathTarget getPosition();
            
            void appendMotion(float, Vector3, Vector3);
            
        private:
            PathTarget currentPosition;
    };
}

#endif