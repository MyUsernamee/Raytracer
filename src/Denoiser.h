//
// Created by dihydromonoxide on 3/5/22.
//

#ifndef RAYTRACER_DENOISER_H
#define RAYTRACER_DENOISER_H


#include <glm/vec3.hpp>
#include "Image.h"

namespace Raytracer {

    namespace Denoiser {

        Image denoise(Image image, int kernelSize);

    }

};


#endif //RAYTRACER_DENOISER_H
