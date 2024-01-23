#include "SceneObject.h"
#include "Material.h"

#ifndef VISIBLE_OBJECT
#define VISIBLE_OBJECT

// a class from which all visible objects will inherit
class VisibleObject : public SceneObject {

    public:

        VisibleObject();
        ~VisibleObject();

        Material getMaterial() {
            return *material;
        }
        void setMaterial(Material *m) {
            material = m;
        }

        virtual void calculateTextureMap(Vector3 point, float &u, float &v) = 0;
        virtual Vector3 getSurfaceNormal(Vector3 point) = 0;
        virtual Ray rayOfRefraction(Ray ray, Vector3 hit) = 0;
        virtual Vector3 rayCastHit(Ray r, ObjectHitData &data) = 0;

    protected:
        Material *material;

};



#endif // VISIBLE_OBJECT