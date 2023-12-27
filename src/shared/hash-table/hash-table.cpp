//
// Created by Johny Georges on 2023-12-26.
//

#include <string>
#include "hash-table.h"
#include "../utils/logger/logger.h"


template <typename T>
HashTable<T>::HashTable() {
    _table = std::unordered_map<std::string, T>();
}

template <typename T>
T* HashTable<T>::get(std::string* key) {
    auto result = _table.find(key);
    if (result == _table.end()) {
        handleNotFound(key);
    } else {
        return result.value;
    }
}

template <typename T>
void HashTable<T>::set(std::string* key, T* value) {
    _table.insert(key, value);
}

template <typename T>
bool HashTable<T>::del(std::string* key) {
    auto deleteCount = _table.erase(key);
    if (deleteCount == 0) {
        return false;
    }
    return true;
}

template <typename T>
void HashTable<T>::merge(HashTable<T>* otherTable) {
    _table.merge(otherTable);
}

template <typename T>
void HashTable<T>::handleNotFound(std::string* key) {
    Logger::log("no value found for key", key);
    throw std::runtime_error("missing key from HashTable");
}
