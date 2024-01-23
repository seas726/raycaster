#include <string>
#include <iostream>
#include "Vector3.h"
#include <vector>
#include "SceneObject.h"
#include "Shapes.h"
#include "VisibleObject.h"
#include "Triangle.h"

#ifndef MESH
#define MESH

// A mesh object is a collection of triangles
class Mesh : public VisibleObject {

    public:
        Mesh();
        ~Mesh();

        Vector3 rayCastHit(Ray ray, ObjectHitData &data);

    private:
        // array of vertecies
        // array of faces
        std::vector<Vector3 *> verticies;
        std::vector<Face *> faces;
};

#endif // Mesh