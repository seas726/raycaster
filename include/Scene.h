#include "Lights.h"
#include "SceneObject.h"
#include "Camera.h"
#include "Shapes.h"
#include "Mesh.h"
#include "Triangle.h"
#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <cmath>
#include <limits>
#include <util.h>

#ifndef SCENE
#define SCENE

class Scene {
    public:
        Scene();
        ~Scene();

        void Render(); // the big fucntion!! will render the scene and spit out an output

        void LoadFromFile(std::string fileName);

        PPMColor TraceRay(Ray ray, int count);
        PPMColor ShadeRay(Ray ray, VisibleObject *shape, Vector3 hit, int count); // Returns proper color for object and point given light intersections
        float ShadowHit(VisibleObject *shape, Vector3 hit, Light *light);
        void setMainCamera(Camera *cam);
        void addObject(VisibleObject *obj);
        void addLight(Light *l);
        Camera *getMainCamera() { return mainCamera; }

        friend std::ostream& operator << (std::ostream& os, const Scene& scene);
        friend std::istream& operator >> (std::istream& is, Scene& scene);
    
    // depricated
    void setBackgroundColor(PPMColor c) {
        backgroundColor = c;
    }

    void setBackgroundMaterial(Material m) {
        backgroundMaterial = m;
    }

    std::vector<VisibleObject *> getshapeObjects() {
        return visibleObjects;
    }
    
    private:
        Camera *mainCamera;
        PPMColor backgroundColor;

        Material backgroundMaterial;
        std::vector<VisibleObject *> visibleObjects;
        //std::vector<ImplicitShapeObject *> shapeObjects;
        std::vector<Mesh *> meshObjects;
        std::vector<Light *> lightObjects;

        std::string name;
        
};
#endif // SCENE
