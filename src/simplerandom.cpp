//
// Created by dihydromonoxide on 2/28/22.
//

#include <ctime>
#include <iostream>
#include <random>
#include <functional>
#include "simplerandom.h"

namespace Raytracer {

    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    auto random = std::bind ( distribution, generator );

    float random_float(){
        float number = random();
        return number;
    }

    void random_seed(int seed){
        generator.seed(seed);
    }

}