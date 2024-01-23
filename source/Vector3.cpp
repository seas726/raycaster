#include "Vector3.h"
#include <cmath>
#include <limits>



Vector3::Vector3() {
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0; // better way to do this but i forgot
}

Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z; // better way to do this but i forgot
}

Vector3::~Vector3() { }

const Vector3 Vector3::null(INFINITY, INFINITY, INFINITY); // vector which not exist
const Vector3 Vector3::zero(0.0f, 0.0f, 0.0f);

float Vector3::getXValue() const { return x; }
float Vector3::getYValue() const { return y; }
float Vector3::getZValue() const { return z; }

void Vector3::setValues(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}


void Vector3::setXValue(float x) { this->x = x; }
void Vector3::setYValue(float y) { this->y = y; }
void Vector3::setZValue(float z) { this->z = z; }

std::ostream& operator << (std::ostream& os, const Vector3& vector) {
    os << "<" << vector.getXValue() << ", " << vector.getYValue() << ", " << vector.getZValue() << ">";
    return os;
}

std::istream& operator >> (std::istream& is, Vector3& vector) {
    is >> vector.x >> vector.y >> vector.z;
    return is;
}

// define boolean operators

bool Vector3::operator == (const Vector3 &other) {
    return this->x == other.x && 
           this->y == other.y && 
           this->z == other.z;
}
bool Vector3::operator != (const Vector3 &other) {
    return !(*this == other);
}
bool Vector3::operator > (const Vector3 &other) {
    return this->x > other.x && 
           this->y > other.y && 
           this->z > other.z;
}
bool Vector3::operator < (const Vector3 &other) {
    return this->x < other.x && 
           this->y < other.y && 
           this->z < other.z;
}



Vector3& Vector3::operator = (const Vector3 &other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    return *this;
}


Vector3& Vector3::operator += (const Vector3 &other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;

    return *this;
}
Vector3& Vector3::operator -= (const Vector3 &other) {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;

    return *this;

}
Vector3& Vector3::operator *= (const float &scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
}
Vector3& Vector3::operator /= (const float &scalar) {
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;

    return *this;
}


float Vector3::distance(Vector3 other) {
    float dist = 0;

    dist = sqrt(powf(x - other.x, 2) + powf(y - other.y, 2) + powf(z - other.z, 2));

    return dist;
}

float Vector3::dotProduct(const Vector3 other) {
    float product;

    product = (this->x * other.x) + (this->y * other.y) + (this->z * other.z);

    return product;

}

Vector3 Vector3::crossProduct(Vector3 other) {
    Vector3 product;

    product.setXValue((this->y * other.z) - (this->z * other.y));
    product.setYValue((this->z * other.x) - (this->x * other.z));
    product.setZValue((this->x * other.y) - (this->y * other.x));

    return product;
}



float Vector3::getLength() {
    return sqrt((x * x) + (y * y) + (z * z));
}

void Vector3::normalize() {
    float l = this->getLength();
    
    this->x = this->x/l;
    this->y = this->y/l;
    this->z = this->z/l;
}

/*
void Vector3::setValues(Vector3 *other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}
 */
Vector3 operator + (Vector3 v1, const Vector3 &v2) {
    v1 += v2;
    return v1;
}

Vector3 operator - (Vector3 v1, const Vector3 &v2) {
    v1 -= v2;
    return v1;
}

Vector3 operator * (Vector3 vector, const float &scalar) {
    vector *= scalar;
    return vector;
}

Vector3 operator / (Vector3 vector, const float &scalar) {
    vector /= scalar;
    return vector;
}