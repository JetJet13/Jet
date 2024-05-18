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
    this->initLiteralTypeSignatures();
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

IntLiteralTypeSignature* TypeSignatureLookupTable::getIntLiteralTypeSignature() {
    return (IntLiteralTypeSignature*)this->find(LiteralTypeSignatureName::INT);
}

FloatLiteralTypeSignature* TypeSignatureLookupTable::getFloatLiteralTypeSignature() {
    return (FloatLiteralTypeSignature*)this->find(LiteralTypeSignatureName::FLOAT);
}

CharLiteralTypeSignature* TypeSignatureLookupTable::getCharLiteralTypeSignature() {
    return (CharLiteralTypeSignature*)this->find(LiteralTypeSignatureName::CHAR);
}

StringLiteralTypeSignature* TypeSignatureLookupTable::getStringLiteralTypeSignature() {
    return (StringLiteralTypeSignature*)this->find(LiteralTypeSignatureName::STRING);
}

BoolLiteralTypeSignature* TypeSignatureLookupTable::getBoolLiteralTypeSignature() {
    return (BoolLiteralTypeSignature*)this->find(LiteralTypeSignatureName::BOOL);
}

void TypeSignatureLookupTable::dump() {
    Logger::log("======== TypeSignatureLookupTable DUMP ========");
    for (auto keyValue : _typeSignatureLookupTable) {
        Logger::log("KEY - ", keyValue.first, "VALUE - ", keyValue.second->toString());
    }
    Logger::log("===============================================");
}


void TypeSignatureLookupTable::initLiteralTypeSignatures() {
    this->insert(LiteralTypeSignatureName::INT, new IntLiteralTypeSignature());
    this->insert(LiteralTypeSignatureName::FLOAT, new FloatLiteralTypeSignature());
    this->insert(LiteralTypeSignatureName::CHAR, new CharLiteralTypeSignature());
    this->insert(LiteralTypeSignatureName::STRING, new StringLiteralTypeSignature());
    this->insert(LiteralTypeSignatureName::BOOL, new BoolLiteralTypeSignature());
}
