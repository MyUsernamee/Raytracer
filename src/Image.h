//
// Created by dihydromonoxide on 3/5/22.
//

#ifndef RAYTRACER_IMAGE_H
#define RAYTRACER_IMAGE_H


#include <glm/vec3.hpp>

struct Image {

    int width;
    int height;
    glm::vec3** pixels;


};


#endif //RAYTRACER_IMAGE_H
