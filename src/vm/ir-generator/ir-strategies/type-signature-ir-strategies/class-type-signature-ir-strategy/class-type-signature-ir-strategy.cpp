//
// Created by Johny Georges on 2024-07-11.
//

#include "class-type-signature-ir-strategy.h"

IRType* ClassTypeSignatureIRStrategy::generate(ClassTypeSignature* classTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto classPropertyTypes = std::vector<llvm::Type*>();
    for (auto keyValue : classTypeSignature->getProperties()->getKeyValues()) {
        classPropertyTypes.push_back(
            irGenerator->generateTypeFor(keyValue.second->getTargetTypeSignature())->getType()
        );
    }
    return new IRType(llvm::StructType::get(**context, classPropertyTypes));
}