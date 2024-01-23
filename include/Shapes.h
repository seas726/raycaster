#include "VisibleObject.h"

#ifndef SHAPES
#define SHAPES

// Define the 3D shapes that can be represented in this Raycaster

class Sphere : public VisibleObject {

    public:
        Sphere();
        Sphere(float radius);
        Sphere(Vector3 pos, float radius);

        float getVolume();

        // Rendering
        Vector3 rayCastHit(Ray ray, ObjectHitData &data); 
        void calculateTextureMap(Vector3 point, float &u, float &v);
        Vector3 getSurfaceNormal(Vector3 point);
        Ray rayOfRefraction(Ray ray, Vector3 hit);


    private:
        float radius;
};

class Cylinder : public VisibleObject {
    public:
        Cylinder();
        Cylinder(float radius, float height);
        Cylinder(Vector3 pos, float radius, float height);

        float getVolume(); 
        Vector3 rayCastHit(Ray ray, ObjectHitData &data);

    private:
        float radius;
        float height;
};

#endif
