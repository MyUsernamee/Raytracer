//
// Created by dihydromonoxide on 3/6/22.
//

#include <future>
#include <thread>
#include <glm/glm.hpp>
#include <vector>
#include "ThreadUtilities.h"

namespace Raytracer{

    namespace ThreadUtilities {

        // Takes a function with arbitrary inputs and outputs and runs it across many threads
        // Returns a vector of the results
        template<typename T, typename _Args>
        std::vector<T> run_threads(std::function<T(_Args)> func, int num_threads) {
            std::vector<T> results;
            std::vector<std::future<T>> futures;
            for (int i = 0; i < num_threads; i++) {
                futures.push_back(std::async(std::launch::async, func));
            }
            for (auto &f : futures) {
                results.push_back(f.get());
            }
            return results;
        }

    }

}