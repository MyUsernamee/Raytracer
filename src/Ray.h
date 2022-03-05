//
// Created by dihydromonoxide on 2/27/22.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Raytracer {

    struct Ray {

    public:

        glm::vec3 origin;
        glm::vec3 direction;

    };

}

#endif //RAYTRACER_RAY_H
