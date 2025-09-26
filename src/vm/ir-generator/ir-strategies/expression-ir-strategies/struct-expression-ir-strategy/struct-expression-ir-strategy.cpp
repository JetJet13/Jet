//
// Created by Johny Georges on 2024-06-21.
//

#include "struct-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

IRStructExpressionNode* StructExpressionIRStrategy::generate(ASTStructExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto structValues = std::vector<IRExpressionNode*>();
    auto structValueSourceAllocationMap = std::unordered_map<std::string, IRInstructionNode*>();
    for (auto keyValuePair : node->getKeyValuePairs()) {
        auto irNode = irGenerator->generateFor(keyValuePair->getValue(), scope, irContext, irOperation);
        structValues.push_back(irNode);
        if (irNode->getSourceAllocation()) {
            structValueSourceAllocationMap.insert(
                std::pair(keyValuePair->getKey()->getId() , irNode->getSourceAllocation().value())
            );
        }
    }
    return new IRStructExpressionNode(
            node,
            this->generateStructAllocation(node, irType, structValueSourceAllocationMap, irGenerator, irContext, irOperation),
            irType,
            structValues
    );
}

IRInstructionNode* StructExpressionIRStrategy::generateStructAllocation(ASTStructExpressionNode* node, IRStructType* irType, std::unordered_map<std::string, IRInstructionNode*> structValueSourceAllocationMap, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation) {
    if (node->isReferenced() || irOperation->isCopyGlobal() || irOperation->isRefGlobalAssignment()) {
        auto malloc = llvm::CallInst::Create(
                irContext->getIRModule()->getMallocFunction()->getFunctionType(),
                irContext->getIRModule()->getMallocFunction(),
                { irGenerator->generateInt64Constant(irType->getSizeInBytes()) },
                ""
        );
        return IRInstructionNodeFactory::create(
                malloc,
                irGenerator->generateIrPointerType(irType),
                {},
                std::move(structValueSourceAllocationMap)
        );
    }
    return IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType), std::move(structValueSourceAllocationMap));
}