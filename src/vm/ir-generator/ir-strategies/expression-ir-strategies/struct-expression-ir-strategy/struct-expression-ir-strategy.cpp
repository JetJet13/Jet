//
// Created by Johny Georges on 2024-06-21.
//

#include "struct-expression-ir-strategy.h"
#include "../../../../utils/address-space-generator/address-space-generator.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"

llvm::Value* StructExpressionIRStrategy::generate(ASTStructExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    auto structType = this->generateStructType(node, context, irGenerator, scope);
    return new llvm::AllocaInst(
            structType,
            AddressSpaceGenerator::generate(structType),
            nullptr,
            DataAlignmentGenerator::generate(structType));
}

llvm::StructType* StructExpressionIRStrategy::generateStructType(ASTStructExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {

    auto structValueTypes = std::vector<llvm::Type*>();
    for (auto keyValuePairs : node->getKeyValuePairs()) {
        structValueTypes.push_back(irGenerator->generateFor(keyValuePairs->getValue(), scope)->getType());
    }

    return llvm::StructType::get(**context, structValueTypes);
}