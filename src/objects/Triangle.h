//
// Created by dihydromonoxide on 3/6/22.
//

#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H

#include "RaytracedObject.h"
#include "Vertex.h"
#include <glm/glm.hpp>
#include <vector>

namespace Raytracer {

    class Triangle : public RaytracedObject {

    public:

        void Init(std::vector<Vertex> vertices, glm::vec3 position, glm::mat4 orientation, glm::vec3 scale, Material material);
        Triangle(std::vector<Vertex> vertices, glm::vec3 position, glm::mat4 orientation, glm::vec3 scale, Material material);
        Triangle(std::vector<Vertex> vertices, glm::vec3 position, glm::vec3 scale, Material material);
        Triangle(std::vector<Vertex> vertices, glm::vec3 position, glm::vec3 scale);
        Triangle(std::vector<Vertex> vertices, glm::vec3 position);
        Triangle(std::vector<Vertex> vertices);
        Triangle();

        HitData intersect(Ray ray);

        std::vector<Vertex> getVertices();

        void setVertices(std::vector<Vertex>);


    private:

        std::vector<Vertex> vertices;

    };

}

#endif //RAYTRACER_TRIANGLE_H
