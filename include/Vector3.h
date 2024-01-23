// A class to define a Vector in 3D space
// Designed to inherit?

#include <iostream>


#ifndef VECTOR3
#define VECTOR3


// change this to a struct?? maybe/ why/ why not idk.
class Vector3 {
    
    public:
    
        Vector3();
        Vector3(float x, float y, float z);
        
        ~Vector3();


        float data[3];

        static const Vector3 null;
        static const Vector3 zero;

        
    
        // getters
        float getXValue() const;
        float getYValue() const;
        float getZValue() const;
    
        // setters

        void setValues(float x, float y, float z);

        void setXValue(float x);
        void setYValue(float y);
        void setZValue(float z);

        // math
        float dotProduct(Vector3 other);
        Vector3 crossProduct(Vector3 other);

        float distance(Vector3 other);
    
        // operator overload
        friend std::ostream& operator << (std::ostream& os, const Vector3& vector);
        friend std::istream& operator >> (std::istream& is, Vector3& vector);


        bool operator == (const Vector3 &other);
        bool operator != (const Vector3 &other);
        bool operator > (const Vector3 &other);
        bool operator < (const Vector3 &other);

        Vector3& operator = (const Vector3 &other);

        Vector3& operator += (const Vector3 &other);
        Vector3& operator -= (const Vector3 &other);
        Vector3& operator *= (const float &scalar);
        Vector3& operator /= (const float &scalar);
        
        friend Vector3 operator + (Vector3 v1, const Vector3 &v2);
        friend Vector3 operator - (Vector3 v1, const Vector3 &v2);
        friend Vector3 operator * (Vector3 vector, const float &scalar);
        friend Vector3 operator / (Vector3 vector, const float &scalar);
    
    
        //void setValues(Vector3 other);
        
        float getLength();
        void normalize();
        
        
    private:
        // x y and z values to represent magnitude and such
        float x;
        float y;
        float z;
        
        //float length; // maybe store length every time value is updated?
};



#endif
