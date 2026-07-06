//
// Created by Johny Georges on 2024-06-21.
//

#include "struct-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

std::shared_ptr<IRStructExpressionNode> StructExpressionIRStrategy::generate(std::shared_ptr<ASTStructExpressionNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto irType = irGenerator->generateTypeFor(node->getStructTypeSignature(), scope, irContext);
    auto structValues = std::vector<std::shared_ptr<IRExpressionNode>>();
    auto structValueSourceAllocationMap = std::unordered_map<std::string, std::shared_ptr<IRInstructionNode>>();
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
    return std::make_shared<IRStructExpressionNode>(
            node,
            structRefAllocation,
            irGenerator->generateArcAllocation(irContext),
            irType,
            structValues
    );
}

std::shared_ptr<IRInstructionNode> StructExpressionIRStrategy::generateStructAllocation(std::shared_ptr<IRStructType> irType, std::unordered_map<std::string, std::shared_ptr<IRInstructionNode>> structValueSourceAllocationMap, IRGenerator* irGenerator, IRContext* irContext) {
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

std::shared_ptr<IRInstructionNode> StructExpressionIRStrategy::generateStructRefAllocation(std::shared_ptr<ASTStructExpressionNode> node, std::shared_ptr<IRStructRefType> irType, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation) {
    return IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
}