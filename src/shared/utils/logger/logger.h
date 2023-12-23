//
// Created by Johny Georges on 2023-12-23.
//

#ifndef JETLANG_LOGGER_H
#define JETLANG_LOGGER_H
#include "iostream"

namespace Logger {
    template <typename... Types>
    void log(Types... args) {
        ((std::cout << args << ' '), ...);
        std::cout << std::endl;
    }
    void log(const char* strings[], int size, const char* prefix = "", const char* suffix = "");
    void log(int nums[], int size, const char* prefix = "", const char* suffix = "");
};
#endif //JETLANG_LOGGER_H
