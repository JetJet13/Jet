//
// Created by Johny Georges on 2024-05-03.
//

#include "type-signature-lookup-table.h"
#include "../../../type-signature/literal-type-signature/types/literal-type-signature-name.h"
#include "../../../type-signature/unknown-type-signature/unknown-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"

TypeSignatureLookupTable::TypeSignatureLookupTable(std::optional<TypeSignatureLookupTable*> outerScope) {
    _typeSignatureLookupTable = std::unordered_map<std::string, TypeSignature*>();
    _outerScope = outerScope;
}

TypeSignatureLookupTable* TypeSignatureLookupTable::insert(std::string key, TypeSignature* typeSignature) {
    _typeSignatureLookupTable.insert(std::pair<std::string, TypeSignature*>(key, typeSignature));
    return this;
}

TypeSignature* TypeSignatureLookupTable::find(std::string key) {
    auto result = _typeSignatureLookupTable.find(key);
    if (result == _typeSignatureLookupTable.end()) {
        if (_outerScope) {
            return _outerScope.value()->find(key);
        }
        return new UnknownTypeSignature();
    } else {
        return result->second;
    }
}

void TypeSignatureLookupTable::dump() {
    Logger::log("======== TypeSignatureLookupTable DUMP ========");
    for (auto keyValue : _typeSignatureLookupTable) {
        Logger::log("KEY - ", keyValue.first, "VALUE - ", keyValue.second->toString());
    }
    if (_outerScope) {
        _outerScope.value()->dump();
    }
    Logger::log("===============================================");
}
