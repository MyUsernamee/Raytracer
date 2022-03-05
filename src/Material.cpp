//
// Created by dihydromonoxide on 2/28/22.
//

#include <iostream>
#include "Material.h"

namespace Raytracer {

    Material::Material(const glm::vec3 &color, float diffuse, float emission) {

        this->color = color;
        this->diffuse = diffuse;
        this->emission = emission;

    }

    glm::vec3 Material::calculateOutgoingDirection(glm::vec3 incoming, glm::vec3 normal) {

        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 right = glm::normalize(glm::cross(up, normal + glm::vec3(0.0001f)));
        up = glm::cross(normal, right);

        glm::vec3 specular = glm::reflect(incoming, normal);

        glm::vec3 diffuse = normal * random_float() + right * (random_float() - 0.5f) + up * (random_float() - 0.5f);
        diffuse = glm::normalize(diffuse);

        glm::vec3 outgoing = diffuse * this->diffuse + specular * (1.0f - this->diffuse);

        return outgoing;

    }

    Material::Material() {

        this->color = glm::vec3(1.0f);
        this->diffuse = 1.0f;
        this->emission = 0.0f;

    }

}