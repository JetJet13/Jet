//
// Created by Johny Georges on 2023-12-24.
//

#include "to-string.h"

namespace ToStringUtil {
    std::string toString(uint8_t value) {
        return std::to_string(value);
    }
    std::string toString(int value) {
        return std::to_string(value);
    }
    std::string toString(bool value) {
        return value ? "true" : "false";
    }

}