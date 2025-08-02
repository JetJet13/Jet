//
// Created by Johny Georges on 2024-05-06.
//

#include "bool-literal-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

std::string BoolLiteralTypeSignature::toDetailString() {
    return "bool";
}

std::string BoolLiteralTypeSignature::toString() {
    return "BOOL_LITERAL_TYPE_SIGNATURE";
}

TypeSource BoolLiteralTypeSignature::getTypeSource() {
    return BOOL_LITERAL_TYPE_SOURCE;
}
