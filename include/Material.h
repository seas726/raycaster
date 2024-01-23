#include <vector>
#include "Color.h"
#include "Image.h"
#include "Vector3.h"
#include "data.h"

#ifndef MATERIAL
#define MATERIAL

class Material {
    
    public:
    
        Material();
        ~Material();

        // Macro Materials
        static const Material null;

        // gettters
        PPMColor getColor();
        PPMColor getSpecular() { return specular; }
        Vector3 getWeight();
        float getOpacity();
        float getRefractionIndex();
        PPMImage *getTexture() { return texture;}
        int getN() { return n; }

        // setters
        void setColor(PPMColor c) { this->color = c; }
        void setSpecular(PPMColor spec) { this->specular = spec; }
        void setWeight(Vector3 w);
        void setWeight(float a, float d, float s);
        void setTexture(PPMImage *texture); 
        void setN(int n) { this->n = n; } 

        friend std::ostream& operator << (std::ostream& os, const Material& material);
        friend std::istream& operator >> (std::istream& is, Material& material);
        
    private:
        PPMImage *texture;
        PPMColor color;
        PPMColor specular;
        Vector3 weight; // weights [0-1] to represent ambient, diffuse, specular
        int n;
        float opacity;
        float refraction_index;
};

#endif
