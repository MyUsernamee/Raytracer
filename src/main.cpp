#include <iostream>
#include <glm/glm.hpp>

#include "World.h"
#include "objects/RaytracedObject.h"
#include "objects/Plane.h"
#include "Material.h"


using namespace Raytracer;

#define WIDTH 512
#define HEIGHT 512
#define SAMPLES 64
#define SCALE 8.0f
#define SCENE 1
#define OBJECTS 40

int main() {

#ifdef GENERATE_TEST_IMAGE

    glm::vec3 **image = new glm::vec3*[WIDTH];

    for (int i = 0; i < WIDTH; i++) {
        image[i] = new glm::vec3[HEIGHT];
        for(int j = 0; j < HEIGHT; j++) {
            image[i][j] = glm::vec3((float)i / WIDTH, (float)j / HEIGHT, 0.0f);
        }
    }

    World::writeImage(image, WIDTH, HEIGHT, "pixel_coords.png");

#else

    time_t start, end;
    time(&start);

    World* world = new World();

#if SCENE == 0

    world->setCamera(glm::vec3(0, 2, 0), glm::vec3(0, 0, 1));

    // Floor
    world->addObject(new Plane(glm::vec3(0, -1, 1),
                               glm::vec3(0, 1, 0),
                               glm::vec3(1.0f),
                               Material(glm::vec3(1.0f), 1.0, 0.0)));
    // Ceiling
    world->addObject(new Plane(glm::vec3(0, 1, 1),
                               glm::vec3(0, -1, 0),
                               glm::vec3(1.0f),
                               Material(glm::vec3(1.0f), 1.0, 0.0)));
    // Right wall
    world->addObject(new Plane(glm::vec3(-1, 0, 1),
                               glm::vec3(1, 0, 0),
                               glm::vec3(1.0f),
                               Material(glm::vec3(0, 0, 1.0), 1.0, 0.0)));
    // Left wall
    world->addObject(new Plane(glm::vec3(1, 0, 1),
                               glm::vec3(-1, 0, 0),
                               glm::vec3(1.0f),
                               Material(glm::vec3(1.0, 0, 0), 1.0, 0.0)));
    // Back wall
    world->addObject(new Plane(glm::vec3(0, 0, 2),
                               glm::vec3(0, 0, -1),
                               glm::vec3(1.0f),
                               Material(glm::vec3(1.0f, 1.0f, 1.0f), 0.2, 0.0)));
    // Front wall
    world->addObject(new Plane(glm::vec3(0, 0, -0.01),
                               glm::vec3(0, 0, 1),
                               glm::vec3(1.0f),
                               Material(glm::vec3(1.0f), 1.0, 0.0)));
    world->addObject(new Sphere(glm::vec3(0, 1, 1.5),
                              glm::toMat4(glm::quatLookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 1))),
                              glm::vec3(0.2f),
                              Material(glm::vec3(1.0f, 0.8f, 0.5f), 1.0, .6)));
    world->addObject(new Sphere(glm::vec3(0, -0.8, 1.5),
                                glm::mat4(1.0f),
                                glm::vec3(0.2f),
                                Material(glm::vec3(0.0f, 1.0f, 0.0), 1.0, 0)));
    //world->addObject(new Sphere(glm::vec3(-0.4, -0.95, 1),
    //                            glm::mat4(1.0f),
    //                            glm::vec3(0.05f),
    //                            Material(glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, 1.0f)));
    //world->addObject(new Sphere(glm::vec3(0.4, 0.5, 1),
    //                            glm::mat4(1.0f),
    //                            glm::vec3(0.05f),
    //                            Material(glm::vec3(0.0f, 1.0f, 1.0f), 1.0f, 1.0f)));
    world->addObject(new Sphere(glm::vec3(-0.5, -0.8, 1.5),
                                glm::mat4(1.0f),
                                glm::vec3(0.2f),
                                Material(glm::vec3(1.0f), 0.4, 0)));


#else

    world->setCamera(glm::vec3(0, 4, -4) * 2.0f, glm::vec3(0, 0, 0));

    world->addObject(new Plane(glm::vec3(0, -1, 0),
                               glm::vec3(0, 1, 0),
                               glm::vec3(100.0f),
                               Material(glm::vec3(1.0f), 1.0, 0.0)));

    world->addObject(new Plane(glm::vec3(4.0f),
                               glm::normalize(glm::vec3(-1.0f)),
                               glm::vec3(2.0f),
                               Material(glm::vec3(1.0f), 1.0, 100.0)));


    for(int i = 0; i < OBJECTS; i = i + 1) {

        float scale = random_float();

        world->addObject(new Sphere(glm::vec3((random_float() * 2.0f - 1.0f) * SCALE, -1.0f + scale, (random_float() * 2.0f - 1.0f) * SCALE),
                                    glm::mat4(1.0f),
                                    glm::vec3(scale),
                                    Material(glm::vec3(random_float(), random_float(), random_float()), random_float(),
                                             random_float() > 0.5 ? random_float() * 10.0 : 0.0f)));

    }

#endif

    Image pixels = world->render(WIDTH, HEIGHT, SAMPLES);

    time(&end);

    Raytracer::World::writeImage(pixels, "desatuatingmapper.png");

    std::cout << "Time: " << difftime(end, start) << " seconds" << std::endl;

#endif

    return 0;
}
