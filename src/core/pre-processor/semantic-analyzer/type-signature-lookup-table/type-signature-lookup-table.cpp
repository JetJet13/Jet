//
// Created by Johny Georges on 2024-05-03.
//

#include "type-signature-lookup-table.h"
#include "../type-signature-generator/types/literal-type-signature-factory.h"
#include "../type-signature-generator/types/literal-type-signature-name.h"

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

void TypeSignatureLookupTable::initLiteralTypeSignatures() {
    this->insert(LiteralTypeSignatureName::INT, LiteralTypeSignatureFactory::createIntLiteralType());
    this->insert(LiteralTypeSignatureName::FLOAT, LiteralTypeSignatureFactory::createFloatLiteralType());
    this->insert(LiteralTypeSignatureName::CHAR, LiteralTypeSignatureFactory::createCharLiteralType());
    this->insert(LiteralTypeSignatureName::STRING, LiteralTypeSignatureFactory::createStringLiteralType());
    this->insert(LiteralTypeSignatureName::BOOL, LiteralTypeSignatureFactory::createBooleanLiteralType());
}