#include "Image.h"

PPMImage::PPMImage() {
    width = 0;
    height = 0;
}
PPMImage::~PPMImage() {

}

void PPMImage::setDimensions(int w, int h) {
    width = w;
    height = h;
}

PPMColor PPMImage::getColor(float u, float v) {

    int j = (u * (width));
    int i = (v * (height));

    return (*texture)[i * width + j];
}

void PPMImage::setArray(std::vector<PPMColor> *t) {
    texture = t;
}



void PPMImage::readFromFile(std::string filename) {

    std::string type;
    int c_space = 0;

    std::ifstream texture_file;

    texture_file.open(filename);

    std::cout << filename << '\n';

    if(!texture_file.is_open()) {
        perror("Something went horribly wrong, could not open texture file\n");
        exit(1);
    }

    texture_file >> type >> this->width >> this->height >> c_space;

    this->texture = new std::vector<PPMColor>();

    for(int i = 0; i < (width * height); i++) {
        PPMColor p;
        int r, g, b;
        texture_file >> r >> g >> b;
        p.setColor(((float)r/255.0f), ((float)g/255.0f), ((float)b/255.0f));
        this->texture->push_back(p);
    }
    texture_file.close();
}
