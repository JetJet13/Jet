//
// Created by Johny Georges on 2024-04-30.
//

#include "class-type.h"

ClassType::ClassType(Lexeme* className) {
    _className = className;
}

Lexeme* ClassType::getName() {
    return _className;
}

TypeSource ClassType::getTypeSource() {
    return CLASS_TYPE_SOURCE;
}

bool ClassType::isEqualTo(BaseType* otherType) {
    if (this->getTypeSource() == otherType->getTypeSource()) {
        return this->getName()->isEqualTo(((ClassType*)otherType)->getName());
    }

    return false;
}