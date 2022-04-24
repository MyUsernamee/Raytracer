//
// Created by dihydromonoxide on 2/28/22.
//

#include <ctime>
#include <iostream>
#include <random>
#include <functional>
#include <thread>
#include "simplerandom.h"

namespace Raytracer {

    float random_float(){
        float seed = std::hash<std::thread::id>{}(std::this_thread::get_id()) * std::chrono::steady_clock::now().time_since_epoch().count();
        //std::cout << seed << std::endl;
        std::default_random_engine generator(seed);
        std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
        return distribution(generator);
    }

}