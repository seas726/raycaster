

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream> 


#include "Vector3.h"
#include "SceneObject.h"
#include "Shapes.h"
#include "Scene.h"


/**
 * @brief entry point for raycaster. this only functions to instantiate a Scene 
 *        object which is the basis of the rendering engine.
 * 
 * @param argc arguement count
 * @param argv arguement values
 * @return int status code
 */

int main(int argc, char **argv) {

    // handle user input
    std::string inputFileName = ""; // reference to filename
    
    // manage input arguements. First arguement is always the program name so argc must be greater than 2.
    if(argc >= 2) {
        inputFileName = argv[1]; // Reference to first command line arg
    }
    else {
        printf("Please input a filename\n"); // error, no valid arguement
        return -1;
    }

    // create a new instance of a scene
    Scene *s = new Scene();


    //load scene objects from file and render
    s->LoadFromFile(inputFileName);
    s->Render();

    // put render functionality here. 
    /*
    
    */



    //delete s;
    return 0;
}
