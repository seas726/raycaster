#include "SceneObject.h"

class Light : public SceneObject {

    public:
        void setColor(PPMColor c) { lightColor = c; }
        PPMColor getColor() {
            return lightColor;
        }
        void setType(int t) { type = t; }
        int getType() { return type; }

        virtual Vector3 getLightVector(Vector3 point) = 0;

    protected:
        PPMColor lightColor;
        float intensity; // [0-1]
        int type;
};

class DirectionalLight : public Light {
    
    public:
        Vector3 getLightVector(Vector3 point) {
            // directional light vector is always the same
            Vector3 L = this->getPosition() * -1;
            L.normalize();
            return L;
        }
};

class PointLight : public Light {

    public:
        Vector3 getLightVector(Vector3 point) {
            Vector3 L = (this->getPosition() - point);
            L.normalize();
            return L;
        }
};

class SpotLight : public Light {
    // angle

};