//
// Created by Johny Georges on 2024-05-06.
//

#include "string-literal-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

std::string StringLiteralTypeSignature::toDetailString() {
    return "string";
}

std::string StringLiteralTypeSignature::toString() {
    return "STRING_LITERAL_TYPE_SIGNATURE";
}

TypeSource StringLiteralTypeSignature::getTypeSource() {
    return STRING_LITERAL_TYPE_SOURCE;
}