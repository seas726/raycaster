#include "Vector3.h"
#include "VisibleObject.h"

#ifndef TRIANGLE
#define TRIANGLE

class Triangle;

struct Face {


    Face() {
        for(int i = 0; i < 3; i++) {
            verticies[i] = -1;
            normals[i] = -1;
            textures[i] = -1;
        }
    }

    int verticies[3];
    int normals[3];
    int textures[3];

    friend std::ostream& operator << (std::ostream& os, Face& face);
    friend std::istream& operator >> (std::istream& is, Face& face);

/*
    Triangle makeTriangle(std::vector<Vector3> verts, std::vector<Vector3> norms) {
        Triangle t;

        for(int i = 0; i < 3; i++) {

        }

        return t;
    }
    */
};

class Triangle : public VisibleObject {

    public:
        Triangle();
        Triangle(Vector3 p0, Vector3 p1, Vector3 p2);

        Vector3 getV0() { return v0; }
        Vector3 getV1() { return v1; }
        Vector3 getV2() { return v2; }
        
        Vector3 rayCastHit(Ray ray, ObjectHitData &data);
        void calculateTextureMap(Vector3 point, float &u, float &v);
        Vector3 getSurfaceNormal(Vector3 point);
        virtual Ray rayOfRefraction(Ray ray, Vector3 hit);


        void setVerts(Vector3 v0, Vector3 v1, Vector3 v2);
        void setTextMaps(int texts[3][2]);
        void setNorms(Vector3 n0, Vector3 n1, Vector3 n2);

        friend std::ostream& operator << (std::ostream& os, Triangle& face);
        friend std::istream& operator >> (std::istream& is, Triangle& face);

    private:
        Vector3 v0, v1, v2;
        Vector3 t0, t1, t2;
        Vector3 n0, n1, n2;

        int text[3][2];

        Vector3 barycentric;
};

#endif