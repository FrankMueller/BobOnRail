#ifndef BobOnRails_Firmware_GyroSensor_H
#define BobOnRails_Firmware_GyroSensor_H

namespace BobOnRails::Firmware {

    class Vector3 {
        public:
            float X;
            float Y;
            float Z;
    
            float length() const;
            
            static Vector3 add(Vector3 v1, Vector3 v2);
            
            static Vector3 subtract(Vector3 v1, Vector3 v2);
            
            static Vector3 scale(Vector3 v, float scale);
            
            inline Vector3 operator+(Vector3 v) const;
            
            inline Vector3 operator-(Vector3 v) const;
            
            inline Vector3 operator-() const;
            
            inline Vector3 operator*(float factor) const;
    }
}

#endif