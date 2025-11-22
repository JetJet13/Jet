//
// Created by Johny Georges on 2025-11-21.
//

#include "lambda-scope-type-signature-ir-strategy.h"

IRStructType* LambdaScopeTypeSignatureIRStrategy::generate(LambdaScopeTypeSignature* lambdaScopeTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto structPropertyTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, unsigned long>();
    auto keyTypeMap = std::unordered_map<std::string, IRType*>();
    auto capturedVariableIds = lambdaScopeTypeSignature->getCapturedVariableIds();
    for (int i = 0; i < capturedVariableIds->size(); ++i) {
        auto capturedVariableId = capturedVariableIds->at(i);
        auto irType = scope->find(capturedVariableId).value()->getIRType();
        structPropertyTypes.push_back(irType->getType());
        keyIndexMap.insert(
                std::pair(capturedVariableId, i)
        );
        keyTypeMap.insert(std::pair(capturedVariableId, irType));
    }
    auto structType = new IRStructType(llvm::StructType::get(**irContext->getContext(), structPropertyTypes), keyIndexMap, keyTypeMap);
    return structType;
}