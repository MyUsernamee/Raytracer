//
// Created by dihydromonoxide on 2/28/22.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include <glm/glm.hpp>
#include "simplerandom.h"

namespace Raytracer {

    struct Material {

    public:
        Material();
        Material(const glm::vec3 &color, float diffuse, float emission);

        glm::vec3 color;
        float diffuse;
        float emission;

        glm::vec3 calculateOutgoingDirection(glm::vec3 incoming, glm::vec3 normal);

    };

}


#endif //RAYTRACER_MATERIAL_H
