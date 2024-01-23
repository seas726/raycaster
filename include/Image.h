#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Color.h"



#ifndef IMAGE
#define IMAGE


class PPMImage {


    public:
        PPMImage();
        ~PPMImage();

        void setDimensions(int w, int  h);

        PPMColor getColor(float u, float v);
        void setArray(std::vector<PPMColor> *t);

        void readFromFile(std::string filename);

    private:
        std::vector<PPMColor> *texture;
        int width;
        int height;
};

#endif // TEXTURE