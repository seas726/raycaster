// Define a color system to use!
// Make sure all color types are interchangeable and inherit from base color functions.

#include <iostream>
#include "util.h"

#ifndef COLOR
#define COLOR

class Color {
    
    
};

// RGB Colors [0-1]

class PPMColor {
    
public:
    PPMColor();
    PPMColor(float r, float g, float b);
    ~PPMColor();

    static const PPMColor white;
    static const PPMColor black;
    static const PPMColor red;
    static const PPMColor green;
    static const PPMColor blue;

    
    void setColor(float r, float g, float b);
    float getRed() const { return r; }
    float getGreen() const { return g; }
    float getBlue() const { return b; }

    friend std::ostream& operator << (std::ostream& os, const PPMColor& color);
    friend std::istream& operator >> (std::istream& is, PPMColor& color);

    bool operator == (const PPMColor &other);
    bool operator != (const PPMColor &other);

    bool operator > (const PPMColor &other);
    bool operator < (const PPMColor &other);
    
    bool operator >= (const PPMColor &other);
    bool operator <= (const PPMColor &other);

    PPMColor& operator = (const PPMColor &other);

    PPMColor& operator += (const PPMColor &other);
    PPMColor& operator -= (const PPMColor &other);

    PPMColor& operator *= (const float &other);
    PPMColor& operator /= (const float &other);

    friend PPMColor operator + (PPMColor c1, const PPMColor &other);
    friend PPMColor operator - (PPMColor c1, const PPMColor &other);
    
    friend PPMColor operator * (PPMColor c1, const float &scalar);
    friend PPMColor operator / (PPMColor c1, const float &scalar);

    static PPMColor clampColor();



    private:
        float r;
        float g;
        float b;
};

#endif
