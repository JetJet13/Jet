//
// Created by Johny Georges on 2024-06-21.
//

#include "struct-expression-ir-strategy.h"

IRStructExpressionNode* StructExpressionIRStrategy::generate(ASTStructExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto structValueTypes = std::vector<llvm::Type*>();
    auto structValues = std::vector<IRExpressionNode*>();
    for (auto keyValuePair : node->getKeyValuePairs()) {
        auto irNode = irGenerator->generateFor(keyValuePair->getValue(), scope, irModule);
        structValues.push_back(irNode);
        structValueTypes.push_back(irNode->getType());
    }

    return new IRStructExpressionNode(
            node,
            llvm::ConstantStruct::get(llvm::StructType::get(**context, structValueTypes)),
            structValues
    );
}