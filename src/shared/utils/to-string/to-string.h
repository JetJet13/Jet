//
// Created by Johny Georges on 2023-12-24.
//

#ifndef JETLANG_TO_STRING_H
#define JETLANG_TO_STRING_H

#include <string>

namespace ToStringUtil {
    template <typename T>
    std::string toString(T value) {
        return "???";
    }
    std::string toString(uint8_t value);
    std::string toString(int value);
    std::string toString(bool value);
}
#endif //JETLANG_TO_STRING_H
