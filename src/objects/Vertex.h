//
// Created by dihydromonoxide on 3/6/22.
//

#ifndef RAYTRACER_VERTEX_H
#define RAYTRACER_VERTEX_H

#include <glm/glm.hpp>


namespace Raytracer {

    struct Vertex {

        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;

        Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords) : position(position), normal(normal), texCoords(texCoords) {}

    };

}

#endif //RAYTRACER_VERTEX_H
