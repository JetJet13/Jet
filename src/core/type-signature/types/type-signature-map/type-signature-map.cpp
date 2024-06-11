//
// Created by Johny Georges on 2024-05-03.
//

#include "type-signature-map.h"
#include "../../literal-type-signature/literal-type-signature.h"
#include "../../struct-type-signature/struct-key-value-type-signature/struct-key-value-type-signature.h"
#include "../../class-type-signature/class-property-type-signature/class-property-type-signature.h"
#include "../../class-type-signature/class-constructor-type-signature/class-constructor-type-signature.h"
#include "../../class-type-signature/class-method-type-signature/class-method-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"

template<class T>
TypeSignatureMap<T>::TypeSignatureMap() {
    _typeSignatureMap = std::unordered_map<std::string, T*>();
}

template<class T>
TypeSignatureMap<T>::TypeSignatureMap(std::vector<std::pair<std::string, T*>> keyValuePairs) {
    _typeSignatureMap = std::unordered_map<std::string, T*>();
    for (auto keyValuePair : keyValuePairs) {
        _typeSignatureMap.insert(keyValuePair);
    }
}

template<class T>
std::optional<T*> TypeSignatureMap<T>::find(std::string key) {
    auto result = _typeSignatureMap.find(key);
    if (result == _typeSignatureMap.end()) {
        return {};
    } else {
        return result->second;
    }
}

template<class T>
TypeSignatureMap<T>* TypeSignatureMap<T>::insert(std::string key, T* value) {
    _typeSignatureMap.insert(std::pair<std::string, T*>(key, value));
    return this;
}

template<class T>
bool TypeSignatureMap<T>::isEqualTo(TypeSignatureMap<T>* other) {
    if (this->size() != other->size()) {
        return false;
    }

    for (const auto& type : _typeSignatureMap) {
        if (!other->find(type.first)) {
            Logger::log("type signature map, did not find type!", type.first);
            return false;
        }

        if (!other->find(type.first).value()->isEqualTo(type.second)) {
            Logger::log("type signature map, not equal!", type.first);
            return false;
        }
    }
    return true;
}

template<class T>
std::vector<std::pair<std::string, T*>> TypeSignatureMap<T>::getKeyValues() {
    auto keyValues = std::vector<std::pair<std::string, T*>>();
    for (auto keyValue : _typeSignatureMap) {
        keyValues.push_back(keyValue);
    }
    return keyValues;
}

template<class T>
unsigned long TypeSignatureMap<T>::size() {
    return _typeSignatureMap.size();
}


template<class T>
void TypeSignatureMap<T>::print() {
    for (auto type : _typeSignatureMap) {
        Logger::log("ID", type.first);
        type.second->print();
    }
}

template class TypeSignatureMap<LiteralTypeSignature>;
template class TypeSignatureMap<TypeSignature>;
template class TypeSignatureMap<ClassPropertyTypeSignature>;
template class TypeSignatureMap<ClassConstructorTypeSignature>;
template class TypeSignatureMap<ClassMethodTypeSignature>;
