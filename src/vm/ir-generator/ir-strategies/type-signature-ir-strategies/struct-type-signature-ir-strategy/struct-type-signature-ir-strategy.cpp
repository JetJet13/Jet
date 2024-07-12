//
// Created by Johny Georges on 2024-07-11.
//

#include "struct-type-signature-ir-strategy.h"

IRType* StructTypeSignatureIRStrategy::generate(StructTypeSignature* structTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto structPropertyTypes = std::vector<llvm::Type*>();
    for (auto keyValue : structTypeSignature->getKeyValuePairs()->getKeyValues()) {
        structPropertyTypes.push_back(
                irGenerator->generateTypeFor(keyValue.second->getTargetTypeSignature())->getType()
        );
    }
    return new IRType(llvm::StructType::get(**context, structPropertyTypes));
}