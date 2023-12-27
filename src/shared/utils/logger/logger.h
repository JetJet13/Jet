//
// Created by Johny Georges on 2023-12-23.
//

#ifndef JETLANG_LOGGER_H
#define JETLANG_LOGGER_H
#include <string>
#include "iostream"


namespace Logger {
    template <typename... Types>
    void log(Types... args) {
        ((std::cout << args << ' '), ...);
        std::cout << std::endl;
    }
};
#endif //JETLANG_LOGGER_H
