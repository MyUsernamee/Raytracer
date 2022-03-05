//
// Created by dihydromonoxide on 3/3/22.
//

#include "Plane.h"

namespace Raytracer {

    void Plane::Init(glm::vec3 position, glm::vec3 normal, glm::vec3 scale, Material material) {

        this->position = position;
        this->normal = normal;
        this->scale = scale;
        this->material = material;

        // Now we calculate the plane's orientation

        // First we find the axis with the smallest absolute dot value
        float upDot = std::abs(glm::dot(glm::vec3(0, 1, 0), normal));
        float rightDot = std::abs(glm::dot(glm::vec3(1, 0, 0), normal));
        float forwardDot = std::abs(glm::dot(glm::vec3(0, 0, 1), normal));

        glm::mat4 orientation;

        // Then we find the axis with the largest absolute dot value
        if(upDot < rightDot && upDot < forwardDot){
            glm::vec3 right = glm::cross(normal, glm::vec3(0, 1, 0));
            glm::vec3 up = glm::cross(right, normal);
            orientation = glm::mat4(right.x, right.y, right.z, 0,
                                    up.x, up.y, up.z, 0,
                                    normal.x, normal.y, normal.z, 0,
                                    0, 0, 0, 1);
        }
        else if (rightDot <= forwardDot){
            glm::vec3 up = glm::cross(normal, glm::vec3(1, 0, 0));
            glm::vec3 right = glm::cross(up, normal);
            orientation = glm::mat4(right.x, right.y, right.z, 0,
                                    up.x, up.y, up.z, 0,
                                    normal.x, normal.y, normal.z, 0,
                                    0, 0, 0, 1);
        }
        else{
            glm::vec3 up = glm::cross(normal, glm::vec3(0, 0, 1));
            glm::vec3 right = glm::cross(up, normal);
            orientation = glm::mat4(right.x, right.y, right.z, 0,
                                    up.x, up.y, up.z, 0,
                                    normal.x, normal.y, normal.z, 0,
                                    0, 0, 0, 1);
        }

        glm::vec3 testVector = glm::vec3(0, 1, 0);
        testVector = glm::vec3(glm::vec4(testVector, 1) * orientation);

        this->orientation = orientation;

    }

    Plane::Plane(glm::vec3 position, glm::vec3 normal) {

        this->Init(position, normal, glm::vec3(1.0f, 1.0f, 1.0f), Material());

    }

    Plane::Plane(glm::vec3 position, glm::vec3 normal, glm::vec3 scale, Material material) {

        this->Init(position, normal, scale, material);

    }

    Plane::Plane(glm::vec3 position, glm::vec3 normal, glm::vec3 scale) {

        this->Init(position, normal, scale, Material());

    }

    Plane::Plane(glm::vec3 position) : RaytracedObject(position) {

        this->Init(position, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), Material());

    }
    HitData Plane::intersect(Ray ray) {

#ifdef OLD_PLANE_INTERSECTION

        glm::vec3 planeNormal = this->getNormal(glm::vec3(0.0, 0.0, 0.0));
        float a = glm::dot(-planeNormal, ray.origin - this->getPosition());
        if(a > 0){
            return {false, -1.0, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), this};
        }
        glm::vec3 relativePosition = this->getNormal(glm::vec3(0.0, 0.0, 0.0)) * a;
        a = glm::dot(glm::normalize(relativePosition), ray.direction);
        float b = glm::length(relativePosition);
        if (a <= 0) {
            return {false, -1.0, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), this};
        }
        float t = b / a;
        glm::vec3 hitPoint = ray.origin + ray.direction * t;
        return {true, t, this->getNormal(hitPoint), hitPoint, this};

#else

        // First we convert the ray origin and direction to the plane's local space
        glm::vec3 rayOrigin = ray.origin - this->getPosition();
        rayOrigin = glm::vec3(glm::vec4(rayOrigin, 1.0f) * this->orientation);
        glm::vec3 rayDirection = ray.direction;

        // Now we calculate the t
        float a = glm::dot(-this->normal, rayDirection);
        if (a <= 0)
            return {false, ray, -1.0, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), this};
        float t = rayOrigin.z / a;

        // Now we calculate the hit point
        glm::vec3 hitPoint = ray.origin + rayDirection * t;
        glm::vec3 localHitPoint = glm::vec3(glm::vec4(hitPoint - this->getPosition(), 1.0f) * this->orientation);

        if(std::abs(localHitPoint.x) > this->scale.x || std::abs(localHitPoint.y) > this->scale.y)
            return  {false, ray, -1.0, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), this};

        // Then we return the hit data
        return {true, ray, t, this->normal, hitPoint, this};


#endif

    }

    glm::vec3 Plane::getNormal(glm::vec3 point) {
        return this->normal;
    }

}