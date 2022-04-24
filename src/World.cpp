//
// Created by dihydromonoxide on 2/27/22.
//

#include "World.h"

#define SATURATE_COLOR

namespace Raytracer {

    Raytracer::World::World() {
        this->sampleThreads = std::vector<std::thread*>();
        this->objects = std::vector<RaytracedObject *>();
        this->cameraMatrix = glm::lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));
        this->cameraPosition = glm::vec4(0.0, 0.0, -1.0, 0.0);
    }

    Raytracer::World::World(std::vector<RaytracedObject *> objects) {
        this->sampleThreads = std::vector<std::thread*>();
        this->objects = objects;
        this->cameraMatrix = glm::lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));
        this->cameraPosition = glm::vec4(0.0, 0.0, -1.0, 0.0);
    }

    Raytracer::World::~World() {
        for (auto object: this->objects) {
            delete object;
        }
    }

    Image Raytracer::World::render(int width, int height, int samples) {

        auto** pixels = new glm::vec3*[width];
        auto** objectBuffer = new glm::vec3*[width];
        auto** normalBuffer = new glm::vec3*[width];
        auto** albedoBuffer = new glm::vec3*[width];

        auto* samplesBuffer = new Image*[samples];

        for(int sample = 0; sample < samples; sample++) {

            Image* image = new Image();

            this->queueSampleThread(width, height, image);
            samplesBuffer[sample] = image;

        }

        for(int sample = 0; sample < samples; sample++) {
            this->sampleThreads[sample]->join();
            for(int x = 0; x < width; x++) {
                // If this row is not allocated yet, allocate it
                if(pixels[x] == nullptr) {
                    pixels[x] = new glm::vec3[height];
                }
                for(int y = 0; y < height; y++) {
                    pixels[x][y] += samplesBuffer[sample]->pixels[x][y] * glm::vec3(1.0 / samples);
                }
            }
            std::cout << "Sample " << sample << " done" << std::endl;
        }

        return {width, height, pixels};

    }

    Image Raytracer::World::renderImage(int width, int height) {

        auto** pixels = new glm::vec3*[width];
        auto** objectBuffer = new glm::vec3*[width];
        auto** normalBuffer = new glm::vec3*[width];
        auto** albedoBuffer = new glm::vec3*[width];

        float ratio = (float)width / (float)height;

        for (int i = 0; i < width; i++) {
            pixels[i] = new glm::vec3[height];
            for (int j = 0; j < height; j++) {
                pixels[i][j] = glm::vec3(0.0f, 0.0f, 0.0f);

                float u = (float) i / (float) width * 2.0 - 1.0;
                float v = (float) j / (float) height * 2.0 - 1.0;
                u = u * ratio;

                glm::vec3 direction = glm::normalize(glm::vec3(u, v, 1.0f));
                glm::vec3 worldDirection =  glm::vec4(direction, 1.0) * this->cameraMatrix;
                Ray ray = {glm::vec3(this->getCameraPosition()), worldDirection};

                HitData hitData = this->intersect(ray);

                pixels[i][j] = this->trace(hitData, glm::vec3(1.0f), glm::vec3(0.0f), 4, true);

                pixels[i][j] = this->mapColor(pixels[i][j]);
            }
        }

        return {width, height, pixels};

    }

    void Raytracer::World::addObject(Raytracer::RaytracedObject *object) {
        if(object->getMaterial().emission > 0.0) {
            this->lights.push_back(object);
        }
        this->objects.push_back(object);
    }

    Raytracer::RaytracedObject *Raytracer::World::removeObject(Raytracer::RaytracedObject *object) {
        for (auto it = this->objects.begin(); it != this->objects.end(); it++) {
            if (*it == object) {
                this->objects.erase(it);
                return object;
            }
        }
        return nullptr;
    }

    Raytracer::RaytracedObject *Raytracer::World::removeObject(int index) {
        RaytracedObject *object = this->objects[index];
        this->objects.erase(this->objects.begin() + index);
        return object;
    }

    Raytracer::RaytracedObject *Raytracer::World::getObject(int index) {
        return objects[index];
    }

    void Raytracer::World::setObject(int index, Raytracer::RaytracedObject *object) {
        objects[index] = object;
    }

    int Raytracer::World::getObjectCount() {
        return this->objects.size();
    }

    Raytracer::HitData Raytracer::World::intersect(Raytracer::Ray ray) {

        HitData bestHit = HitData();
        bestHit.t = std::numeric_limits<float>::max();

        for (auto object: this->objects) {
            HitData hit = object->intersect(ray);
            if (hit.t < bestHit.t && hit.hit) {
                bestHit = hit;
            }
        }

        return bestHit;

    }

    glm::mat4 World::getCameraMatrix() {
        return this->cameraMatrix;
    }

    void World::setCameraMatrix(glm::mat4 cameraMatrix) {
        this->cameraMatrix = cameraMatrix;
    }

    void World::writeImage(Image image, const std::string& filename) {

        int width = image.width;
        int height = image.height;
        glm::vec3** pixels = image.pixels;

        png::image<png::rgb_pixel> pngImage(width, height);

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                pngImage.set_pixel(i, j, png::rgb_pixel(pixels[i][j].x * 255, pixels[i][j].y * 255, pixels[i][j].z * 255));
            }
        }

        pngImage.write(filename);

    }

    std::vector<RaytracedObject *> World::getObjects() {
        return this->objects;
    }

    glm::vec4 World::getCameraPosition() {
        return this->cameraPosition;
    }

    void World::setCameraPosition(glm::vec4 cameraPosition) {
        this->cameraPosition = cameraPosition;
    }

    void World::setCamera(glm::vec3 cameraPosition, glm::vec3 cameraTarget) {

        this->cameraPosition = glm::vec4(cameraPosition, 1.0f);
        glm::vec3 cameraDirection = glm::normalize(cameraTarget - cameraPosition);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 right = glm::normalize(glm::cross(cameraDirection, up));
        up = glm::normalize(glm::cross(cameraDirection, right));
        this->cameraMatrix = glm::mat4(right.x, right.y, right.z, 0.0f,
                                       up.x, up.y, up.z, 0.0f,
                                       cameraDirection.x, cameraDirection.y, cameraDirection.z, 0.0f,
                                       0.0f, 0.0f, 0.0f, 1.0f);

    }

    glm::vec3 World::trace(HitData hitData, glm::vec3 color, glm::vec3 light, int depth, bool firstHit) {

        if(!hitData.hit || depth < 0) {
            return glm::vec3(0.0f);
        }

        if(hitData.object->getMaterial().emission > 0.0 && firstHit) {
            float lightSurfaceDistance = glm::length(hitData.object->getPosition() - hitData.point);
            return (color * hitData.object->getMaterial().color) * hitData.object->getMaterial().emission;
        }
        else if(hitData.object->getMaterial().emission > 0.0) {

            return glm::vec3(0.0f);

        }

        glm::vec3 normal = hitData.normal;
        glm::vec3 point = hitData.point;

        glm::vec3 lightContribution = this->calculateLighting(hitData);

        glm::vec3 newColor = color
                * hitData.object->getMaterial().color;

        Ray outgoingRay = {point, hitData.object->getMaterial().calculateOutgoingDirection(hitData.ray.direction, normal)};


        if(hitData.object->getMaterial().diffuse < 1){
            return this->trace(outgoingRay, newColor, lightContribution, depth - 1, true) + newColor * lightContribution;
        }

        return this->trace(outgoingRay, newColor, lightContribution, depth - 1, false) + newColor * lightContribution;

    }

    std::vector<RaytracedObject *> World::getLights() {
        return this->lights;
    }

    int World::getLightCount() {
        return this->lights.size();
    }

    glm::vec3 World::calculateLighting(HitData hit) {

        Ray ray = hit.ray;
        glm::vec3 color = glm::vec3(0.0f);

        for (auto light: this->lights) {

            glm::vec3 randomLightPosition = light->getPosition() + glm::vec3(hit.object->getOrientation() * glm::vec4(
                    light->getScale().x * (2 * random_float() - 1),
                    light->getScale().y * (2 * random_float() - 1),
                    light->getScale().z * (2 * random_float() - 1), 1.0f));
            glm::vec3 lightDirection = glm::normalize(randomLightPosition - hit.point);

            Ray ray = {hit.point, lightDirection};
            HitData lightHit = this->intersect(ray);

            if(lightHit.hit && lightHit.object == light) {

                float lightSurfaceDistance = lightHit.t + 1.0f;

                color += light->getMaterial().color * light->getMaterial().emission / (lightSurfaceDistance * lightSurfaceDistance) *
                        std::max(glm::dot(lightDirection, hit.normal), 0.0f) * hit.object->getMaterial().diffuse;

            }

        }

        return color;

    }

    glm::vec3 World::trace(Ray ray, glm::vec3 color, glm::vec3 light, int depth) {
        return this->trace(ray, color, light, depth, true);
    }

    glm::vec3 World::trace(Ray hit, glm::vec3 color, glm::vec3 light, int depth, bool firstHit) {

        return this->trace(this->intersect(hit), color, light, depth, firstHit);

    }

    glm::vec3 World::trace(HitData hit, glm::vec3 color, glm::vec3 light, int depth) {
        return this->trace(hit, color, light, depth, true);
    }

    glm::vec3 World::mapColor(glm::vec3 color) {

#ifdef SATURATE_COLOR

        if(color == glm::vec3(0.0f)) {
            return glm::vec3(0.0f);
        }

        // Simple HDR color mapping
        float max = std::max(std::max(color.x, color.y), color.z);

        return color / max * (max / (max + 1.0f));

#else

        return color / (color + glm::vec3(1.0f));

#endif

    }

   std::thread* World::queueSampleThread(int width, int height,
                                  Image *result) {

        std::thread* thread = new std::thread(&World::traceThread, this, width, height, result);
        this->sampleThreads.push_back(thread);

        return thread;

    }

    void World::traceThread(int width, int height, Image* result) {

        *result = this->renderImage(width, height);
        return;


    }


}