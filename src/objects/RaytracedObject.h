//
// Created by dihydromonoxide on 2/27/22.
//

#ifndef RAYTRACER_RAYTRACEDOBJECT_H
#define RAYTRACER_RAYTRACEDOBJECT_H

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../Ray.h"
#include "../Material.h"

#define RAYTRACED_OBJECT(name) class name : public RaytracedObject {\
    using RaytracedObject::RaytracedObject; \
    public:\
        HitData intersect(Ray ray);\
        glm::vec3 getNormal(glm::vec3 point); \
    };

namespace Raytracer {

    class RaytracedObject;

    struct HitData{

    public:

        bool hit;
        Ray ray;
        float t;
        glm::vec3 normal;
        glm::vec3 point;
        RaytracedObject *object;
    };

    class RaytracedObject {

    public:

        RaytracedObject();
        explicit RaytracedObject(glm::vec3 position);
        RaytracedObject(glm::vec3 position, glm::mat4 orientation);
        RaytracedObject(glm::vec3 position, glm::mat4 orientation, glm::vec3 scale);
        RaytracedObject(glm::vec3 position, glm::mat4 orientation, glm::vec3 scale, Material material);

        virtual HitData intersect(Ray ray);
        virtual glm::vec3 getNormal(glm::vec3 point);

        glm::vec3 getPosition();
        glm::mat4 getOrientation();
        glm::vec3 getScale();
        Material getMaterial();

        void setPosition(glm::vec3 position);
        void setOrientation(glm::mat4 orientation);
        void setScale(glm::vec3 scale);
        void setMaterial(Material material);

    protected:

        glm::vec3 position;
        glm::mat4 orientation;
        glm::vec3 scale;
        Material material;

    };

    RAYTRACED_OBJECT(Sphere)



}

#endif //RAYTRACER_RAYTRACEDOBJECT_H
