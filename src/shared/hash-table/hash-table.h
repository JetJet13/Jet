//
// Created by Johny Georges on 2023-12-26.
//

#ifndef JETLANG_HASH_TABLE_H
#define JETLANG_HASH_TABLE_H
#include <string>
#include <unordered_map>

template <typename T>
class HashTable {
private:
    std::unordered_map<std::string, T> _table;
protected:
    virtual void handleNotFound(std::string* key) = 0;
public:
    HashTable();
    T* get(std::string* key);
    void set(std::string* key, T* value);
    bool del(std::string* key);
    void merge(HashTable<T>* otherTable);

};
#endif //JETLANG_HASH_TABLE_H
