//
// Created by dihydromonoxide on 3/6/22.
//

#include "Triangle.h"

namespace Raytracer {

    void Raytracer::Triangle::Init(std::vector<Vertex> vertices, glm::vec3 position, glm::mat4 orientation, glm::vec3 scale,
                                   Raytracer::Material material) {

        this->vertices = vertices;
        this->position = position;
        this->orientation = orientation;
        this->scale = scale;
        this->material = material;

    }

    Raytracer::Triangle::Triangle(std::vector<Vertex> vertices, glm::vec3 position, glm::mat4 orientation, glm::vec3 scale,
                                  Raytracer::Material material) {

        Init(vertices, position, orientation, scale, material);

    }

    Raytracer::Triangle::Triangle(std::vector<Vertex> vertices, glm::vec3 position, glm::vec3 scale, Raytracer::Material material) {

        Init(vertices, position, glm::mat4(1.0f), scale, material);

    }

    Raytracer::Triangle::Triangle(std::vector<Vertex> vertices, glm::vec3 position, glm::vec3 scale) {

        Init(vertices, position, glm::mat4(1.0f), scale, Raytracer::Material());

    }

    Raytracer::Triangle::Triangle(std::vector<Vertex> vertices, glm::vec3 position) {

        Init(vertices, position, glm::mat4(1.0f), glm::vec3(1.0f), Raytracer::Material());

    }

    Raytracer::Triangle::Triangle(std::vector<Vertex> vertices) {

        Init(vertices, glm::vec3(0.0f), glm::mat4(1.0f), glm::vec3(1.0f), Raytracer::Material());

    }

    Raytracer::Triangle::Triangle() {

        Init(std::vector<Vertex>(), glm::vec3(0.0f), glm::mat4(1.0f), glm::vec3(1.0f), Raytracer::Material());

    }

    Raytracer::HitData Raytracer::Triangle::intersect(Raytracer::Ray ray) {

        glm::vec3 origin = this->orientation * glm::vec4(ray.origin - this->position, 0.0f);
        glm::vec3 direction = this->orientation * glm::vec4(ray.direction, 0.0f);

        glm::vec3 vertex0ToVertex1 = vertices[1].position - vertices[0].position;
        glm::vec3 vertex0ToVertex2 = vertices[2].position - vertices[0].position;
        glm::vec3 normal = glm::normalize(glm::cross(vertex0ToVertex1, vertex0ToVertex2));
        float a = glm::dot(normal, origin);
        if (a < 0.0f) {
            normal = -normal;
        }

        // Not Finished yet.

        return HitData();
    }

    std::vector<Raytracer::Vertex> Raytracer::Triangle::getVertices() {
        return std::vector<Vertex>();
    }

    void Raytracer::Triangle::setVertices(std::vector<Vertex>) {

    }

}
