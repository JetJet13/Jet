//
// Created by Johny Georges on 2024-05-03.
//

#ifndef JETLANG_TYPE_SIGNATURE_MAP_H
#define JETLANG_TYPE_SIGNATURE_MAP_H

#include <unordered_map>
#include "type-signature.h"

template<class T = TypeSignature>
class TypeSignatureMap {
private:
    std::unordered_map<std::string, T*> _typeSignatureMap;
public:
    TypeSignatureMap();
    std::optional<T*> find(std::string key);
    void insert(std::string key, T* value);
    bool isEqualTo(TypeSignatureMap<T>* other);
    unsigned long size();
    void print();
};

#endif //JETLANG_TYPE_SIGNATURE_MAP_H
