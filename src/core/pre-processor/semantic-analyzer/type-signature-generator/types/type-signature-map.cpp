//
// Created by Johny Georges on 2024-05-03.
//

#include "type-signature-map.h"
#include "procedure-type-signature.h"

template<class T>
TypeSignatureMap<T>::TypeSignatureMap() {
    _typeSignatureMap = std::unordered_map<std::string, T*>();
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
void TypeSignatureMap<T>::insert(std::string key, T* value) {
    _typeSignatureMap.insert(std::pair<std::string, T*>(key, value));
}

template<class T>
bool TypeSignatureMap<T>::isEqualTo(TypeSignatureMap<T>* other) {
    if (this->size() != other->size()) {
        return false;
    }

    for (auto type : _typeSignatureMap) {
        if (!other->find(type.first)) {
            return false;
        }
    }
    return true;
}

template<class T>
unsigned long TypeSignatureMap<T>::size() {
    return _typeSignatureMap.size();
}


template<class T>
void TypeSignatureMap<T>::print() {
    for (auto type : _typeSignatureMap) {
        type.second->print();
    }
}