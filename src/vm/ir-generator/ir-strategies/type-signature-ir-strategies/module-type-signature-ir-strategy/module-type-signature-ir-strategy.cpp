//
// Created by Johny Georges on 2024-10-29.
//

#include "module-type-signature-ir-strategy.h"

IRPointerType* ModuleTypeSignatureIRStrategy::generate(ModuleTypeSignature* moduleTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    return irGenerator->generateIrPointerType();
}

IRModuleType* ModuleTypeSignatureIRStrategy::generate(ModuleTypeSignature* moduleTypeSignature, std::vector<llvm::Value*> values, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto enumPropertyTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, unsigned long>();
    auto keyTypeMap = std::unordered_map<std::string, IRType*>();
    for (int i = 0; i < moduleTypeSignature->getKeyValuePairs()->size(); ++i) {
        // todo - implement
    }

    return new IRModuleType(llvm::StructType::get(**context, enumPropertyTypes), keyIndexMap, keyTypeMap);
}