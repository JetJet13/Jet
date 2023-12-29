//
// Created by Johny Georges on 2023-12-26.
//

#ifndef JETLANG_HASH_TABLE_H
#define JETLANG_HASH_TABLE_H
#include <string>
#include <unordered_map>
#include "../utils/logger/logger.h"
#include "../utils/to-string/to-string.h"

template <class K, class T, class H>
class HashTable {
private:
    std::unordered_map<K, T, H> _table;
public:
    HashTable() {
        _table = std::unordered_map<K, T, H>();
    }
    T& get(K key) {
        auto result = _table.find(key);
        if (result == _table.end()) {
            return nullptr;
        } else {
            return result->second;
        }
    }
    void set(K key, T value) {
        _table.insert(std::pair<K, T>(key, value));
    }
    bool del(K key) {
        auto deleteCount = _table.erase(key);
        if (deleteCount == 0) {
            return false;
        }
        return true;
    }
    void merge(HashTable<K,T, H>* otherTable) {
        _table.merge(otherTable);
    }

};
#endif //JETLANG_HASH_TABLE_H
