//
// Created by Johny Georges on 2024-05-03.
//

#ifndef JETLANG_TYPE_SIGNATURE_MAP_H
#define JETLANG_TYPE_SIGNATURE_MAP_H

#include <unordered_map>
#include "../../type-signature.h"

template<class T = TypeSignature>
class TypeSignatureMap {
private:
    std::unordered_map<std::string, T*> _typeSignatureMap;
    std::vector<std::string> _typeSignatureKeyList;
public:
    TypeSignatureMap();
    explicit TypeSignatureMap(std::vector<std::pair<std::string, T*>> keyValuePairs);
    std::optional<T*> find(std::string key);
    unsigned long findKeyIndex(std::string key);
    std::string findKeyByIndex(unsigned long index);
    TypeSignatureMap<T>* insert(std::string key, T* value);
    bool isEqualTo(TypeSignatureMap<T>* other);
    bool isEquivalentTo(TypeSignatureMap<T>* other);
    std::vector<std::pair<std::string, T*>> getKeyValues();
    std::vector<std::string> getKeys();
    std::vector<T*> getValues();
    unsigned long size();
    void print();
};

#endif //JETLANG_TYPE_SIGNATURE_MAP_H
