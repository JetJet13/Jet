//
// Created by Johny Georges on 2024-06-08.
//

#include "invocable-type-signature.h"

bool InvocableTypeSignature::isInvocable() {
    return true;
}

bool InvocableTypeSignature::isEquivalentTo(TypeSignature* otherType) {
    if (!otherType->isInvocable()) {
        return false;
    }

    auto other = (InvocableTypeSignature*)otherType;
    if (!this->getReturnType()->isEquivalentTo(other->getReturnType())) {
        return false;
    }

    if (this->getParameterTypes()->size() != other->getParameterTypes()->size()) {
        return false;
    }

    for (int i = 0; i < this->getParameterTypes()->size(); ++i) {
        if (!this->getParameterTypes()->at(i)->isEquivalentTo(other->getParameterTypes()->at(i))) {
            return false;
        }
    }
    return true;
}