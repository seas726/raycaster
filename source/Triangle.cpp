#include "Triangle.h"



Triangle::Triangle() {
    v0 = Vector3::zero;
    v1 = Vector3::zero;
    v2 = Vector3::zero;

    n0 = Vector3::zero;
    n1 = Vector3::zero;
    n2 = Vector3::zero;

    barycentric = Vector3::zero;

}
Triangle::Triangle(Vector3 p0, Vector3 p1, Vector3 p2)  {
    v0 = p0;
    v1 = p1;
    v2 = p2;
}



std::istream& operator >> (std::istream &is, Face &face) {
    
    std::string rest; // string in which to store the rest of the input stream line
    std::getline(is, rest);

    int(&v)[3] = face.verticies;
    int(&t)[3] = face.textures;
    int(&n)[3] = face.normals;

    // scan in all values, verts, textures, and normals
    if(sscanf(rest.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d", &v[0], &t[0], &n[0], &v[1], &t[1], &n[1], &v[2], &t[2], &n[2]) == 9);

    // scan in verts and normals
    else if(sscanf(rest.c_str(), "%d//%d %d//%d %d//%d", &v[0], &n[0], &v[1], &n[1], &v[2], &n[2]) == 6);

    // scan in verts and textures
    else if(sscanf(rest.c_str(), "%d/%d %d/%d %d/%d", &v[0], &t[0], &v[1], &t[1], &v[2], &t[2]) == 6);

    // scan in only verts
    else if(sscanf(rest.c_str(), "%d %d %d", &v[0], &v[1], &v[2]) == 3);
    else {
        perror("Could not read proper face format from file. Please check formatting.\n");
        exit(1);
    }

    return is;
}

std::ostream& operator << (std::ostream& os, Face& face) {
    os << "[< " << face.verticies[0] << ", " << face.verticies[1] << ", " << face.verticies[2] << ">\n"
       << "< " << face.textures[0] << ", " << face.textures[1] << ", " << face.textures[2] << ">\n"
       << "< " << face.normals[0] << ", " << face.normals[1] << ", " << face.normals[2] << ">]";
    return os;
}


std::istream& operator >> (std::istream& is, Triangle& triangle) {
    is >> triangle.v0 >> triangle.v1 >> triangle.v2;
    return is;
}

std::ostream& operator << (std::ostream& os, Triangle& triangle) {
    os << "[" << triangle.getV0() << ", " << triangle.getV1()  << ", "<< triangle.getV2() << "]";
    return os;
}


Vector3 Triangle::rayCastHit(Ray ray, ObjectHitData &data) {

    float kEps = 0.0005f;

    Vector3 e1 = v1 - v0;
    Vector3 e2 = v2 - v0;

    Vector3 pvec = ray.direction.crossProduct(e2);
    float det = e1.dotProduct(pvec);

    if(det < kEps) return Vector3::null;
    if(fabs(det) < kEps) return Vector3::null;

    float invDet = 1.0f/det;

    Vector3 tvec = ray.position - v0;
    float a = tvec.dotProduct(pvec) * invDet;
    if(a < 0 || a > 1) return Vector3::null;

    Vector3 qvec = tvec.crossProduct(e1);
    float b = ray.direction.dotProduct(qvec) * invDet;
    if(b < 0 || a + b > 1) return Vector3::null;


    float g = 1 - (a+b);

    barycentric.setValues(a,b,g);

    float t = e2.dotProduct(qvec) * invDet;



    return ray.position + (ray.direction * t);
}

Vector3 Triangle::getSurfaceNormal(Vector3 point) {

    Vector3 n;

    if(n1 != Vector3::zero &&
       n2 != Vector3::zero &&
       n0 != Vector3::zero) {

        n = (n1 * barycentric.getXValue() +  
               n2 * barycentric.getYValue() + 
               n0 * barycentric.getZValue());        
    }
    else {
        n = (v1 - v0).crossProduct(v2 - v0);
    }

    n.normalize();

    return n;
}

void Triangle::calculateTextureMap(Vector3 point, float &u, float &v) {
    u = barycentric.getXValue() * text[0][0] +
        barycentric.getYValue() * text[1][0] +
        barycentric.getZValue() * text[2][0];
    v = barycentric.getXValue() * text[0][1] +
        barycentric.getYValue() * text[1][1] +
        barycentric.getZValue() * text[2][1];

    return;
}


void Triangle::setVerts(Vector3 v0, Vector3 v1, Vector3 v2) {
    this->v0 = v0;
    this->v1 = v1;
    this->v2 = v2;
}

void Triangle::setTextMaps(int texts[3][2]) {
    for(int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            this->text[i][j] = texts[i][j];
        }
    }
} 

void Triangle::setNorms(Vector3 n0, Vector3 n1, Vector3 n2) {

    n0.normalize();
    n1.normalize();
    n2.normalize();

    this->n0 = n0;
    this->n1 = n1;
    this->n2 = n2;
}


Ray Triangle::rayOfRefraction(Ray ray, Vector3 hit) {
    return ray;
}

