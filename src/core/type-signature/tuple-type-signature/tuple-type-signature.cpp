//
// Created by Johny Georges on 2024-04-30.
//

#include "tuple-type-signature.h"
#include "../../../shared/utils/logger/logger.h"
#include "../unknown-type-signature/unknown-type-signature.h"

TupleTypeSignature::TupleTypeSignature(std::vector<TypeSignature*>* elementTypes) {
    _elementTypes = elementTypes;
}

std::vector<TypeSignature*>* TupleTypeSignature::getElementTypes() {
    return _elementTypes;
}

TypeSignature* TupleTypeSignature::getTypeSignatureAtIndex(unsigned long index) {
    if (index >= this->size()) {
        return new UnknownTypeSignature();
    }
    return _elementTypes->at(index);
}

unsigned long TupleTypeSignature::size() {
    return _elementTypes->size();
}

std::string TupleTypeSignature::toString() {
    return "TUPLE_TYPE_SIGNATURE";
}

TypeSource TupleTypeSignature::getTypeSource() {
    return TUPLE_TYPE_SOURCE;
}

bool TupleTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (TupleTypeSignature*)otherType;
    for (int i = 0; i < _elementTypes->size(); ++i) {
        if (!_elementTypes->at(i)->isEqualTo(other->getElementTypes()->at(i))) {
            return false;
        }
    }

    return true;
}

void TupleTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto & _elementType : *_elementTypes) {
        _elementType->print();
    }
    Logger::log("----------");
}