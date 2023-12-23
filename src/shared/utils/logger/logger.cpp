//
// Created by Johny Georges on 2023-12-23.
//


#include "array"
#include "logger.h"

namespace Logger {

    void log(const char* strings[], int size, const char* prefix, const char* suffix) {
        for (int i = 1; i < size; ++i) {
            std::cout << prefix << strings[i] << suffix << std::endl;
        }
    }

    void log(int nums[], int size, const char* prefix, const char* suffix) {
        for (int i = 0; i < size; ++i) {
            std::cout << prefix << nums[i] << suffix << std::endl;
        }
    }

}



