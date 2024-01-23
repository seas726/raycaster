#include "SceneObject.h"
#include "Vector3.h"

#ifndef CAMERA
#define CAMERA

class Camera : public SceneObject {
    public:
        Camera();
        //Camera(Vector3 * pos, float hFOV, float vFOV, int h, int w);

        ~Camera();

        int getWidth() { return width; }
        int getHeight() { return height; }
        Vector3 getViewDir() { return view_dir; }
        float getFOV() { return hFOV; }
    
        void setResolution(int w, int h);
        void setViewDir(Vector3 dir);
        void setFOV(float fov) { hFOV = fov; }

    private:
        Vector3 view_dir;
        float hFOV; // horizontal fov in degrees
        int width;
        int height;
};

#endif // CAMERA