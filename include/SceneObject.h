// A class to define any Scene Object in 3D space. Designed to be inherited from.
#include "Vector3.h"
#include "Color.h"
#include "Material.h"
#include <vector>
#include <cmath>
#include <limits>

#ifndef SCENE_OBJECT
#define SCENE_OBJECT



struct Ray {

    Ray() {
        direction = Vector3::zero;
        position = Vector3::zero;
    }
    Ray(Vector3 pos, Vector3 dir) {
        direction = dir;
        direction.normalize();
        position = pos;
    }

    Vector3 position;
    Vector3 direction;
};

class SceneObject {

    public:
        SceneObject();
        SceneObject(Vector3 pos);
        //virtual ~SceneObject() = 0;
        
        // getter
        Vector3 getPosition() { return position; }
        Vector3 getUpDir() { return up_direction; }
        
        // setter
        void setPosition(Vector3 pos);
        void setUpDirection(Vector3 dir);
        
    protected:
        Vector3 position;
        Vector3 up_direction; // A normalized vector which represent the up-direction of the object

        // std::vector<Attribute> attributes;
};

#endif



