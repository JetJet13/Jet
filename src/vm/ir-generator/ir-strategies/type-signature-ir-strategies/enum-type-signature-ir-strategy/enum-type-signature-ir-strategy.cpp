//
// Created by Johny Georges on 2024-07-11.
//

#include "enum-type-signature-ir-strategy.h"

IRType* EnumTypeSignatureIRStrategy::generate(EnumTypeSignature* enumTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto enumPropertyTypes = std::vector<llvm::Type*>();
    auto enumPropertyType = irGenerator->generateTypeFor(enumTypeSignature->getType());
    for (auto keyValue : enumTypeSignature->getKeyValuePairs()->getKeyValues()) {
        enumPropertyTypes.push_back(enumPropertyType->getType());
    }
    return new IRType(llvm::StructType::get(**context, enumPropertyTypes));
}