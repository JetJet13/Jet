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
    _typeSignatureMap = std::unordered_map<std::string, T>();
    _typeSignatureKeyList = std::vector<std::string>();
}

template<class T>
TypeSignatureMap<T>::TypeSignatureMap(std::vector<std::pair<std::string, T>> keyValuePairs) {
    _typeSignatureMap = std::unordered_map<std::string, T>();
    for (auto keyValuePair : keyValuePairs) {
        _typeSignatureMap.insert(keyValuePair);
        _typeSignatureKeyList.push_back(keyValuePair.first);
    }
}

template<class T>
std::optional<T> TypeSignatureMap<T>::find(std::string key) {
    auto result = _typeSignatureMap.find(key);
    if (result == _typeSignatureMap.end()) {
        return {};
    } else {
        return result->second;
    }
}

template<class T>
uint64_t TypeSignatureMap<T>::findKeyIndex(std::string key) {
    for (uint64_t i = 0; i < _typeSignatureKeyList.size(); ++i) {
        if (_typeSignatureKeyList[i] == key) {
            return i;
        }
    }
    throw std::invalid_argument("no index found for key: " + key);
}

template<class T>
std::string TypeSignatureMap<T>::findKeyByIndex(uint64_t index) {
    if (index >= _typeSignatureKeyList.size()) {
        throw std::invalid_argument("no key found for index: " + std::to_string(index));
    }
    return _typeSignatureKeyList[index];
}

template<class T>
TypeSignatureMap<T>* TypeSignatureMap<T>::insert(std::string key, T value) {
    _typeSignatureMap.insert(std::pair<std::string, T>(key, value));
    _typeSignatureKeyList.push_back(key);
    return this;
}

template<class T>
bool TypeSignatureMap<T>::isEqualTo(TypeSignatureMap<T>* other) {
    if (this->size() != other->size()) {
        return false;
    }

    for (const auto& type : _typeSignatureMap) {
        auto otherTypeSignature = other->find(type.first);
        if (!otherTypeSignature) {
            Logger::log("type signature map, did not find type!", type.first);
            return false;
        }

        if (!otherTypeSignature.value()->isEqualTo(type.second)) {
            Logger::log("type signature map, not equal!", type.first);
            otherTypeSignature.value()->print();
            type.second->print();
            return false;
        }
    }
    return true;
}

template<class T>
bool TypeSignatureMap<T>::isEquivalentTo(TypeSignatureMap<T>* other) {
    if (this->size() != other->size()) {
        return false;
    }

    for (const auto& type : _typeSignatureMap) {
        auto otherTypeSignature = other->find(type.first);
        if (!otherTypeSignature) {
            return false;
        }

        if (!otherTypeSignature.value()->isEquivalentTo(type.second)) {
            return false;
        }
    }
    return true;
}

template<class T>
bool TypeSignatureMap<T>::isSatisfiedBy(TypeSignatureMap<T>* other) {

    for (const auto& type : _typeSignatureMap) {
        auto otherTypeSignature = other->find(type.first);
        if (!otherTypeSignature) {
            Logger::log("other type signature is missing", type.first);
            other->print();
            return false;
        }

        if (!otherTypeSignature.value()->isEquivalentTo(type.second)) {
            Logger::log(type.first, "not equivalent to");
            otherTypeSignature.value()->print();
            return false;
        }
    }
    return true;
}

template<class T>
std::vector<std::pair<std::string, T>> TypeSignatureMap<T>::getKeyValues() {
    auto keyValues = std::vector<std::pair<std::string, T>>();
    for (auto key : _typeSignatureKeyList) {
        keyValues.push_back(std::pair(key, this->find(key).value()));
    }
    return keyValues;
}

template<class T>
std::vector<std::string> TypeSignatureMap<T>::getKeys() {
    auto keys = std::vector<std::string>();
    for (const auto& key : _typeSignatureKeyList) {
        keys.push_back(key);
    }
    return keys;
}

template<class T>
std::vector<T> TypeSignatureMap<T>::getValues() {
    auto values = std::vector<T>();
    for (const auto& key : _typeSignatureKeyList) {
        values.push_back(this->find(key).value());
    }
    return values;
}

template<class T>
uint64_t TypeSignatureMap<T>::size() {
    return _typeSignatureMap.size();
}


template<class T>
void TypeSignatureMap<T>::print() {
    for (auto type : _typeSignatureMap) {
        Logger::log("ID", type.first);
        type.second->print();
    }
}

template class TypeSignatureMap<std::shared_ptr<LiteralTypeSignature>>;
template class TypeSignatureMap<std::shared_ptr<TypeSignature>>;
template class TypeSignatureMap<std::shared_ptr<ClassPropertyTypeSignature>>;
template class TypeSignatureMap<std::shared_ptr<ClassConstructorTypeSignature>>;
template class TypeSignatureMap<std::shared_ptr<ClassMethodTypeSignature>>;
