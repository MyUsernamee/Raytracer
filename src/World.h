//
// Created by dihydromonoxide on 2/27/22.
//

#ifndef RAYTRACER_WORLD_H
#define RAYTRACER_WORLD_H

#include <vector>
#include <string>
#include "objects/RaytracedObject.h"
#include <png++/png.hpp>
#include "simplerandom.h"
#include "Image.h"

namespace Raytracer {

    class World {

    public:
        World();
        World(std::vector<RaytracedObject *> objects);

        ~World();

        Image render(int width, int height, int samples);

        void addObject(RaytracedObject *object);

        RaytracedObject* removeObject(RaytracedObject *object);
        RaytracedObject* removeObject(int index);

        RaytracedObject* getObject(int index);
        void setObject(int index, RaytracedObject *object);
        glm::mat4 getCameraMatrix();
        void setCameraMatrix(glm::mat4 cameraMatrix);
        glm::vec4 getCameraPosition();
        void setCameraPosition(glm::vec4 cameraPosition);

        void setCamera(glm::vec3 cameraPosition, glm::vec3 cameraTarget);

        std::vector<RaytracedObject *> getObjects();
        int getObjectCount();
        std::vector<RaytracedObject *> getLights();
        int getLightCount();

        static void writeImage(Image image, const std::string& filename);

        HitData intersect(Ray ray);

        glm::vec3 trace(Ray ray, glm::vec3 color, glm::vec3 light, int depth);
        glm::vec3 trace(Ray ray, glm::vec3 color, glm::vec3 light, int depth, bool firstHit);
        glm::vec3 trace(HitData hit, glm::vec3 color, glm::vec3 light, int depth, bool firstHit);
        glm::vec3 trace(HitData hit, glm::vec3 color, glm::vec3 light, int depth);
        glm::vec3 calculateLighting(HitData hit);

        static glm::vec3 mapColor(glm::vec3 color);

    private:
        std::vector<RaytracedObject*> objects;
        std::vector<RaytracedObject*> lights;
        glm::mat4 cameraMatrix;
        glm::vec4 cameraPosition;
    };


}

#endif //RAYTRACER_WORLD_H
