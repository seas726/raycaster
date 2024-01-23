#include "Shapes.h"
#include <cmath>
#include <iostream>


Sphere::Sphere() {
    this->radius = 1.0;
}
Sphere::Sphere(float radius) {
    
    if(radius <= 0) {
        // bad thing happened
        this->radius = 1.0;
    }
    
    this->radius = radius;
    setPosition(Vector3(0,0,0));
}

Sphere::Sphere(Vector3 pos, float radius) {
    this->radius = radius;
    this->setPosition(pos);
}

Vector3 Sphere::rayCastHit(Ray ray, ObjectHitData &data) {
    // return closest point of contact if a solution exists where the ray intersects the sphere


    float B = 2 * (ray.direction.getXValue() * (ray.position.getXValue() - position.getXValue()) + 
                   ray.direction.getYValue() * (ray.position.getYValue() - position.getYValue()) +
                   ray.direction.getZValue() * (ray.position.getZValue() - position.getZValue()) );

    Vector3 temp = ray.position - position;

    temp.setXValue(temp.getXValue()*temp.getXValue()); // sqaure temp :(
    temp.setYValue(temp.getYValue()*temp.getYValue()); // sqaure :(
    temp.setZValue(temp.getZValue()*temp.getZValue()); // sqaure :(
    
    // temp *= temp; ?

    float C = temp.getXValue() + temp.getYValue() + temp.getZValue() - (this->radius * this->radius);

    float discriminant = (B*B) - (4.0f * C);
    // solution is the ray distance. point is ray.direction * solution.

    // if the ray intersects at any point, calculate and return the closest one.
    
    if(discriminant < 0) return Vector3::null; // no hit whatsoever

    float t0 = (-B + sqrt(discriminant)) / 2.0f;
    float t1 = (-B - sqrt(discriminant)) / 2.0f;


    float t = t1;

    // calculate the corrent distance of hit
    if(t0 > 0 && t1 > 0) {
        // good
        if(t0 < t1) {
            t = t0;
        }
        else {
            t = t1;
        }
    }
    else if(t0 > 0 || t1 > 0) {
        if(t0 > t1) {
            t = t0;
        }
        else {
            t = t1;
        }
    }
    else {
        return Vector3::null;
    }

    return ray.position + (ray.direction * t);
}
 
Vector3 Sphere::getSurfaceNormal(Vector3 point) {

    Vector3 n = point - this->getPosition();
    n.normalize();

    return n;
}

float Sphere::getVolume() {
    return 4.0f/3.0f * 3.14159f * (this->radius * this->radius * this->radius);
}

void Sphere::calculateTextureMap(Vector3 point, float &u, float &v) {

    Vector3 N = getSurfaceNormal(point);

    float theta = atan2(N.getZValue(), N.getXValue()); // vertical
    float gamma = acos(N.getYValue()); // horizontal 
    
    u = 0.5 + (theta / (2 * M_PI)); //  vertical
    v = gamma / M_PI; // horizontal

    return;
}

Ray Sphere::rayOfRefraction(Ray ray, Vector3 hit) {

    // object is opaque, no internal refraction
    if(this->material->getOpacity() == 1) {
        return ray;
    }

    Vector3 I =  ray.direction * -1; // opposite of ray direction
    Vector3 N = getSurfaceNormal(hit);

    float refract_ratio = 1/material->getRefractionIndex(); /// TODO: change later, 1 is for air, make dynamic, maybe add new paramater? Make this recursive somehow? idk
    float cos_theta_in = N.dotProduct(I);

    Vector3 T;

    T = ((N * -1) * sqrt(1 - (pow(refract_ratio,2) * (1 - pow(cos_theta_in, 2))))) + ((N * cos_theta_in) - I) * refract_ratio;

    
    Ray r = Ray(hit, T);
    

    return r;
}
