//
// Created by Johny Georges on 2024-04-30.
//

#include "tuple-type-signature.h"
#include "../../../shared/utils/logger/logger.h"
#include "../unknown-type-signature/unknown-type-signature.h"

TupleTypeSignature::TupleTypeSignature() {
    _keyValuePairs = TypeSignatureMap<TypeSignature>();
}

TupleTypeSignature::TupleTypeSignature(std::vector<TypeSignature*>* elementTypes) {
    _keyValuePairs = TypeSignatureMap<TypeSignature>();
    for (unsigned long i = 0; i < elementTypes->size(); ++i) {
        auto key = std::to_string(i);
        auto value = elementTypes->at(i);
        _keyValuePairs.insert(key, value);
    }
}

TupleTypeSignature::TupleTypeSignature(std::vector<TypeSignature*> elementTypes) {
    _id = "jet.tuple";
    _keyValuePairs = TypeSignatureMap<TypeSignature>();
    for (unsigned long i = 0; i < elementTypes.size(); ++i) {
        auto key = std::to_string(i);
        auto value = elementTypes[i];
        _id += "_" + value->getId();
        _keyValuePairs.insert(key, value);
    }
}

TypeSignatureMap<TypeSignature>* TupleTypeSignature::getKeyValuePairs() {
    return &_keyValuePairs;
}

TypeSignature* TupleTypeSignature::getTypeSignatureForKey(std::string key) {
    auto result = _keyValuePairs.find(key);
    if (result) {
        return result.value();
    }
    return new UnknownTypeSignature();
}

TypeSignature* TupleTypeSignature::getTypeSignatureAtIndex(unsigned long index) {
    if (index >= this->size()) {
        return new UnknownTypeSignature();
    }
    return _keyValuePairs.find(std::to_string(index)).value();
}

unsigned long TupleTypeSignature::size() {
    return _keyValuePairs.size();
}

std::string TupleTypeSignature::toDetailString() {
    std::string detailedString = "jet.tuple.";
    for (auto value : _keyValuePairs.getValues()) {
        detailedString += "_" + value->toDetailString();
    }
    return detailedString;
}

std::string TupleTypeSignature::toString() {
    return "TUPLE_TYPE_SIGNATURE";
}

TypeSource TupleTypeSignature::getTypeSource() {
    return TUPLE_TYPE_SOURCE;
}

bool TupleTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource() || this->getTypeTarget() != otherType->getTypeTarget()) {
        return false;
    }

    auto other = (TupleTypeSignature*)otherType;
    return _keyValuePairs.isEqualTo(other->getKeyValuePairs());
}

void TupleTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    _keyValuePairs.print();
    Logger::log("----------");
}