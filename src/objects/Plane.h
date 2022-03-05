//
// Created by dihydromonoxide on 3/3/22.
//

#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H

#include "RaytracedObject.h"


namespace Raytracer {

    class Plane : public RaytracedObject {

    public:

        void Init(glm::vec3 position, glm::vec3 normal, glm::vec3 scale, Material material);

        Plane(glm::vec3 position, glm::vec3 normal, glm::vec3 scale, Material material);
        Plane(glm::vec3 position, glm::vec3 normal, glm::vec3 scale);
        Plane(glm::vec3 position, glm::vec3 normal);
        Plane(glm::vec3 position);

        HitData intersect(Ray ray);
        glm::vec3 getNormal(glm::vec3 point);

    private:
        glm::vec3 normal;
    };

}


#endif //RAYTRACER_PLANE_H
