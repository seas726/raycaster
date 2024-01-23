#include "Material.h"

Material::Material() {
    color = PPMColor(0.0, 0.0, 0.0);
    specular = PPMColor(1,1,1);
    weight = Vector3(1,1,1);

    texture = nullptr;
}

Material::~Material() {

}

PPMColor Material::getColor() {
    return color;
}

void Material::setTexture(PPMImage *t) {
    this->texture = t;
}

void Material::setWeight(Vector3 w) {
    weight = w;
}

void Material::setWeight(float a, float d, float s) {
    weight.setValues(a,d,s);
}

Vector3 Material::getWeight() {
    return weight;
}

float Material::getOpacity() {
    return opacity;
}

float Material::getRefractionIndex() {
    return refraction_index;
}

std::ostream& operator << (std::ostream& os, const Material& material){


    return os;
}
std::istream& operator >> (std::istream& is, Material& material) {
    
    std::string rest;

    float Rd, Gd, Bd, Rs, Gs, Bs, ka, kd, ks;
    float opacity, refraction_index;
    int n = 0;

    std::getline(is, rest); // read rest of line into the string 'rest'

    int read = sscanf(rest.c_str(), "%f %f %f %f %f %f %f %f %f %d %f %f", &Rd, &Gd, &Bd, &Rs, &Gs, &Bs, &ka, &kd, &ks, &n, &opacity, &refraction_index);

    std::cout << read << '\n';

            switch(read) {
                case 3:
                    material.color.setColor(Rd, Gd, Bd);
                    break;
                case 4:
                    material.color.setColor(Rd, Gd, Bd);
                    material.refraction_index = Rs;
                    break;
                case 6:
                    material.color.setColor(Rd, Gd, Bd);
                    material.specular.setColor(Rs, Gs, Bs);
                    break;
                case 9:
                    material.color.setColor(Rd, Gd, Bd);
                    material.specular.setColor(Rs, Gs, Bs);
                    material.weight.setValues(ka, kd, ks);
                    break;
                case 10:
                    material.color.setColor(Rd, Gd, Bd);
                    material.specular.setColor(Rs, Gs, Bs);
                    material.weight.setValues(ka, kd, ks);
                    material.n = n;
                    break;
                case 12:
                    material.color.setColor(Rd, Gd, Bd);
                    material.specular.setColor(Rs, Gs, Bs);
                    material.weight.setValues(ka, kd, ks);
                    material.n = n;
                    material.opacity = opacity;
                    material.refraction_index = refraction_index;
                    break;
                default:
                    perror("Could not read material from input file\n");
                    exit(1);
            }
    return is;
}