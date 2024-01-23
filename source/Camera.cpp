#include "Camera.h"


Camera::Camera() {
    this->hFOV = 120.0;
    this->width = 500;
    this->height = 512;
    this->view_dir = Vector3(0,0,-1);
}

Camera::~Camera() {
    
}

void Camera::setResolution(int w, int h) {
    this->width = w;
    this->height = h;
}

void Camera::setViewDir(Vector3 dir) {
    dir.normalize();
    this->view_dir = dir;
}