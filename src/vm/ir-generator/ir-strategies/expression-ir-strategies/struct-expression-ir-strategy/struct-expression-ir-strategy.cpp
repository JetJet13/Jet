//
// Created by Johny Georges on 2024-06-21.
//

#include "struct-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

IRStructExpressionNode* StructExpressionIRStrategy::generate(ASTStructExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IROperationType irOperationType) {
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature());
    auto structValues = std::vector<IRExpressionNode*>();
    auto structValueSourceAllocationMap = std::unordered_map<std::string, IRInstructionNode*>();
    for (auto keyValuePair : node->getKeyValuePairs()) {
        auto irNode = irGenerator->generateFor(keyValuePair->getValue(), scope, irModule, irOperationType);
        structValues.push_back(irNode);
        if (irNode->getSourceAllocation()) {
            structValueSourceAllocationMap.insert(
                std::pair(keyValuePair->getKey()->getId() , irNode->getSourceAllocation().value())
            );
        }
    }
    auto structAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType), structValueSourceAllocationMap);
    return new IRStructExpressionNode(node, structAllocation, irType, structValues);
}