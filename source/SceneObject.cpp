#include "SceneObject.h"
#include "Shapes.h"

#include <iostream>

SceneObject::SceneObject() {
    position = Vector3::zero;
    up_direction = Vector3(0,1,0);
}

SceneObject::SceneObject(Vector3 pos) {
    position = pos;
}


void SceneObject::setPosition(Vector3 pos) {
    this->position = pos;
}

void SceneObject::setUpDirection(Vector3 dir) {
    up_direction = dir;
    up_direction.normalize();
}

