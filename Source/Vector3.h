#ifndef BobOnRails_Firmware_GyroSensor_H
#define BobOnRails_Firmware_GyroSensor_H

namespace BobOnRails::Firmware {

    class Vector3 {
        public:
            float X;
            float Y;
            float Z;
  
            Vector3();

            Vector3(float x, float y, float z);

            float length() const;
           
            static Vector3 zero();

            static Vector3 vx();
            
	    static Vector3 vy();
            
	    static Vector3 vz();
            
	    static Vector3 add(Vector3 v1, Vector3 v2);
            
            static Vector3 subtract(Vector3 v1, Vector3 v2);
            
            static Vector3 scale(Vector3 v, float scale);
            
            Vector3 operator+(Vector3 v) const;
            
            Vector3 operator-(Vector3 v) const;
            
            Vector3 operator-() const;
            
            Vector3 operator*(float factor) const;
    };
}

#endif
