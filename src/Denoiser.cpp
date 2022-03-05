//
// Created by dihydromonoxide on 3/5/22.
//

#include "Denoiser.h"

namespace Raytracer {

    namespace Denoiser {

        Image denoise(Image image, int kernelSize){

            int width = image.width;
            int height = image.height;
            glm::vec3** pixels = image.pixels;

            glm::vec3** result = new glm::vec3*[width];

            return {}; // Not implemented yet

        }

    }

}