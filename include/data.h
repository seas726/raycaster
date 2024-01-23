#include "Vector3.h"

#ifndef DATA
#define DATA

struct ObjectHitData {
    Vector3 hit_point;
    Vector3 normal;
    Vector3 hit_dir;
    float distance_to_hit;
    float distance_inside_object;
};

#endif