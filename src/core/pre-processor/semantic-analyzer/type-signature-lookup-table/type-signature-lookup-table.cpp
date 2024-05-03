//
// Created by Johny Georges on 2024-05-03.
//

#include "type-signature-lookup-table.h"
#include "../type-signature-generator/types/literal-type-signature-factory.h"

TypeSignatureLookupTable::TypeSignatureLookupTable() {
    _typeSignatureLookupTable = std::unordered_map<std::string, TypeSignature*>();
    this->initBaseTypeSignatures();
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

void TypeSignatureLookupTable::initBaseTypeSignatures() {
    this->insert("int", LiteralTypeSignatureFactory::createIntLiteralType());
    this->insert("float", LiteralTypeSignatureFactory::createFloatLiteralType());
    this->insert("char", LiteralTypeSignatureFactory::createCharLiteralType());
    this->insert("string", LiteralTypeSignatureFactory::createStringLiteralType());
    this->insert("bool", LiteralTypeSignatureFactory::createBooleanLiteralType());
}