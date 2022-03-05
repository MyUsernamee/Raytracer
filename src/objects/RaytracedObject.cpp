//
// Created by dihydromonoxide on 2/27/22.
//

#include <iostream>
#include "RaytracedObject.h"


namespace Raytracer {

    RaytracedObject::RaytracedObject(glm::vec3 position) {
        this->position = position;
        this->orientation = glm::mat4(1.0f);
        this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    RaytracedObject::RaytracedObject(glm::vec3 position, glm::mat4 orientation) {

        this->position = position;
        this->orientation = orientation;
        this->scale = glm::vec3(1.0f, 1.0f, 1.0f);

    }

    RaytracedObject::RaytracedObject(glm::vec3 position, glm::mat4 orientation, glm::vec3 scale, Material material) {

        this->position = position;
        this->orientation = orientation;
        this->scale = scale;
        this->material = material;

    }

    RaytracedObject::RaytracedObject(glm::vec3 position, glm::mat4 orientation, glm::vec3 scale) {

        this->position = position;
        this->orientation = orientation;
        this->scale = scale;

    }

    HitData RaytracedObject::intersect(Ray ray) {
        return {false, ray, -1.0, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), this};
    }

    glm::vec3 RaytracedObject::getNormal(glm::vec3 point) {
        return {0, 0, 0};
    }

    glm::vec3 RaytracedObject::getPosition() {
        return this->position;
    }
    glm::mat4 RaytracedObject::getOrientation() {
        return this->orientation;
    }
    glm::vec3 RaytracedObject::getScale() {
        return this->scale;
    }

    void RaytracedObject::setPosition(glm::vec3 position) {
        this->position = position;
    }
    void RaytracedObject::setOrientation(glm::mat4 orientation) {
        this->orientation = orientation;
    }
    void RaytracedObject::setScale(glm::vec3 scale) {
        this->scale = scale;
    }

    Material RaytracedObject::getMaterial() {
        return this->material;
    }

    void RaytracedObject::setMaterial(Material material) {
        this->material = material;
    }

    RaytracedObject::RaytracedObject() {
        this->position = glm::vec3(0.0, 0.0, 0.0);
        this->orientation = glm::mat4(1.0f);
        this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
        this->material = Material();
    }


    HitData Sphere::intersect(Ray ray) {

        glm::vec3 rayToSphere = this->getPosition() - ray.origin;
        float a = glm::dot(rayToSphere, ray.direction);

        glm::vec3 closestPoint = ray.origin + ray.direction * a;
        glm::vec3 closestPointToSphere = closestPoint - this->getPosition();

        float b = glm::length(closestPointToSphere);
        b = b * b;
        float c = this->getScale().x;
        c = c * c;
        float d = c - b;

        if (a < d || d < 0){
            return {false, ray, -1.0, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), this};
        }

        float t = a - sqrt(d);
        glm::vec3 hitPoint = ray.origin + ray.direction * t;

        return {true, ray, t, this->getNormal(hitPoint), hitPoint, this};

    }
    glm::vec3 Sphere::getNormal(glm::vec3 point) {
        return glm::normalize(point - this->getPosition());
    }

}


