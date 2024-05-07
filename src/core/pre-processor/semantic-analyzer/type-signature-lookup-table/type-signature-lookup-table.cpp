//
// Created by Johny Georges on 2024-05-03.
//

#include "type-signature-lookup-table.h"
#include "../../../type-signature/literal-type-signature/types/literal-type-signature-name.h"

TypeSignatureLookupTable::TypeSignatureLookupTable() {
    _typeSignatureLookupTable = std::unordered_map<std::string, TypeSignature*>();
    this->initLiteralTypeSignatures();
}

TypeSignatureLookupTable* TypeSignatureLookupTable::insert(std::string key, TypeSignature* typeSignature) {
    _typeSignatureLookupTable.insert(std::pair<std::string, TypeSignature*>(key, typeSignature));
    return this;
}

std::optional<TypeSignature*> TypeSignatureLookupTable::find(std::string key) {
    auto result = _typeSignatureLookupTable.find(key);
    if (result == _typeSignatureLookupTable.end()) {
        return {};
    } else {
        return result->second;
    }
}

IntLiteralTypeSignature* TypeSignatureLookupTable::getIntLiteralTypeSignature() {
    return (IntLiteralTypeSignature*)this->find(LiteralTypeSignatureName::INT).value();
}

FloatLiteralTypeSignature* TypeSignatureLookupTable::getFloatLiteralTypeSignature() {
    return (FloatLiteralTypeSignature*)this->find(LiteralTypeSignatureName::INT).value();
}

CharLiteralTypeSignature* TypeSignatureLookupTable::getCharLiteralTypeSignature() {
    return (CharLiteralTypeSignature*)this->find(LiteralTypeSignatureName::INT).value();
}

StringLiteralTypeSignature* TypeSignatureLookupTable::getStringLiteralTypeSignature() {
    return (StringLiteralTypeSignature*)this->find(LiteralTypeSignatureName::INT).value();
}

BoolLiteralTypeSignature* TypeSignatureLookupTable::getBoolLiteralTypeSignature() {
    return (BoolLiteralTypeSignature*)this->find(LiteralTypeSignatureName::INT).value();
}

void TypeSignatureLookupTable::initLiteralTypeSignatures() {
    this->insert(LiteralTypeSignatureName::INT, new IntLiteralTypeSignature());
    this->insert(LiteralTypeSignatureName::FLOAT, new FloatLiteralTypeSignature());
    this->insert(LiteralTypeSignatureName::CHAR, new CharLiteralTypeSignature());
    this->insert(LiteralTypeSignatureName::STRING, new StringLiteralTypeSignature());
    this->insert(LiteralTypeSignatureName::BOOL, new BoolLiteralTypeSignature());
}