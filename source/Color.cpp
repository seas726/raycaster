#include "Color.h"
#include "util.h"


PPMColor::PPMColor() {
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

PPMColor::PPMColor(float r, float g, float b) {
    setColor(r,g,b);
}

PPMColor::~PPMColor() {
    
}


// set color values and validate 0-1. normalize in the future? or something?

const PPMColor PPMColor::white(1.0f, 1.0f, 1.0f);
const PPMColor PPMColor::black(0.0f, 0.0f, 0.0f);
const PPMColor PPMColor::red(1.0f, 0.0f, 0.0f);
const PPMColor PPMColor::green(0.0f, 1.0f, 0.0f);
const PPMColor PPMColor::blue(0.0f, 0.0f, 1.0f);


void PPMColor::setColor(float r, float g, float b) {

    this->r = utility::clampValue(r);
    this->g = utility::clampValue(g);
    this->b = utility::clampValue(b);
}

std::ostream& operator << (std::ostream& os, const PPMColor& color) {
    os << (int)(color.getRed() * 255.0f) << " " << (int)(color.getGreen() * 255.0f) << " " << (int)(color.getBlue() * 255.0f) << '\n';
    return os;
}
std::istream& operator >> (std::istream& is, PPMColor& color) {

    float red, green, blue;
    is >> red >> green >> blue;
    color.setColor(red, green, blue);

    return is;
}


bool PPMColor::operator == (const PPMColor &other) {
    return this->r == other.r && 
           this->g == other.g && 
           this->b == other.b;
}
bool PPMColor::operator != (const PPMColor &other) {
    return !(*this == other);
}
bool PPMColor::operator > (const PPMColor &other) {
    return this->r > other.r && 
           this->g > other.g && 
           this->b > other.b;
}
bool PPMColor::operator < (const PPMColor &other) {
    return this->r < other.r && 
           this->g < other.g && 
           this->b < other.b;
}

bool PPMColor::operator >= (const PPMColor &other) {
    return this->r >= other.r && 
           this->g >= other.g && 
           this->b >= other.b;
}
bool PPMColor::operator <= (const PPMColor &other) {
    return this->r <= other.r && 
           this->g <= other.g && 
           this->b <= other.b;
}

PPMColor& PPMColor::operator = (const PPMColor &other) {
    this->r = other.r;
    this->g = other.g;
    this->b = other.b;
    return *this;
}

PPMColor& PPMColor::operator += (const PPMColor &other) {
    setColor(r += other.r,
             g += other.g,
             b += other.b);
    return *this;
}

PPMColor& PPMColor::operator -= (const PPMColor &other) {

    setColor(r -= other.r, g -= other.g, b -= other.b);

    return *this;
}

PPMColor& PPMColor::operator *= (const float &scalar) {
    setColor(r *= scalar,
             g *= scalar,
             b *= scalar);
    return *this;
}

PPMColor& PPMColor::operator /= (const float &scalar) {
    setColor(r /= scalar,
             g /= scalar,
             b /= scalar);
    return *this;
}

PPMColor operator + (PPMColor c1,  const PPMColor &other) {

    c1 += other;
    return c1;
}

PPMColor operator - (PPMColor c1, const PPMColor &other) {
    
    c1 -= other;
    return c1;
}

PPMColor operator * (PPMColor c1,  const float &scalar) {

    c1 *= scalar;
    return c1;
}

PPMColor operator / (PPMColor c1, const float &scalar) {
    
    c1 /= scalar;
    return c1;
}



