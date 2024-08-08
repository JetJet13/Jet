//
// Created by Johny Georges on 2024-06-21.
//

#include "struct-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

IRStructExpressionNode* StructExpressionIRStrategy::generate(ASTStructExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature());
    auto structValues = std::vector<IRExpressionNode*>();
    for (auto keyValuePair : node->getKeyValuePairs()) {
        auto irNode = irGenerator->generateFor(keyValuePair->getValue(), scope, irModule);
        auto key = keyValuePair->getKey()->getIdentifierNode()->getId();
        structValues.push_back(irNode);
    }
    auto structAllocation = IRInstructionNodeFactory::create(irGenerator->generatePointerType(irType), &structValues);
    return new IRStructExpressionNode(node, structAllocation, irType, structValues);
}