//
// Created by Johny Georges on 2024-04-30.
//

#include "literal-type.h"


LiteralType::LiteralType(Type type) {
    _coreType = type;
}

Type LiteralType::getType() {
    return _coreType;
}

TypeSource LiteralType::getTypeSource() {
    return LITERAL_TYPE_SOURCE;
}

bool LiteralType::isEqualTo(BaseType* otherType) {
    if (this->getTypeSource() == otherType->getTypeSource()) {
        return this->getType() == ((LiteralType*)otherType)->getType();
    }

    return false;
}