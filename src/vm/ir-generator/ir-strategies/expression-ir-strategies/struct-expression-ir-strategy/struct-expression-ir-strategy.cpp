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
        irNode->markAsAssigned();
        structValues.push_back(irNode);
        if (irNode->getSourceAllocation()) {
            structValueSourceAllocationMap.insert(
                std::pair(keyValuePair->getKey()->getId() , irNode->getSourceAllocation().value())
            );
        }
    }
    auto structAllocation = this->generateStructAllocation(irType->getStructIRType(), structValueSourceAllocationMap, irGenerator, irContext);
    auto structRefAllocation = this->generateStructRefAllocation(node, irType, irGenerator, irContext, irOperation);
    structRefAllocation->setParentAllocation(structAllocation);
    return new IRStructExpressionNode(
            node,
            structRefAllocation,
            irGenerator->generateArcAllocation(irContext),
            irType,
            structValues
    );
}

IRInstructionNode* StructExpressionIRStrategy::generateStructAllocation(IRStructType* irType, std::unordered_map<std::string, IRInstructionNode*> structValueSourceAllocationMap, IRGenerator* irGenerator, IRContext* irContext) {
    auto malloc = llvm::CallInst::Create(
            irContext->getIRModule()->getMallocFunction(),
            {
                irGenerator->generateInt64Constant(1),
                irGenerator->generateInt64Constant(irType->getSizeInBytes())
            },
            ""
    );
    return IRInstructionNodeFactory::create(
            malloc,
            irGenerator->generateIrPointerType(irType),
            {},
            std::move(structValueSourceAllocationMap)
    );
}

IRInstructionNode* StructExpressionIRStrategy::generateStructRefAllocation(ASTStructExpressionNode* node, IRStructRefType* irType, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation) {
    return IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
}