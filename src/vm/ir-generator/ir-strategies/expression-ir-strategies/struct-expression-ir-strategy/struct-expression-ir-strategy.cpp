//
// Created by Johny Georges on 2024-06-21.
//

#include "struct-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

IRStructExpressionNode* StructExpressionIRStrategy::generate(ASTStructExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto structValues = std::vector<IRExpressionNode*>();
    auto structValueSourceAllocationMap = std::unordered_map<std::string, IRInstructionNode*>();
    for (auto keyValuePair : node->getKeyValuePairs()) {
        auto irNode = irGenerator->generateFor(keyValuePair->getValue(), scope, irContext, irOperationType);
        structValues.push_back(irNode);
        if (irNode->getSourceAllocation()) {
            structValueSourceAllocationMap.insert(
                std::pair(keyValuePair->getKey()->getId() , irNode->getSourceAllocation().value())
            );
        }
    }
    return new IRStructExpressionNode(
            node,
            this->generateStructAllocation(node, irType, structValueSourceAllocationMap, irGenerator, irContext, irOperationType),
            irType,
            structValues
    );
}

IRInstructionNode* StructExpressionIRStrategy::generateStructAllocation(ASTStructExpressionNode* node, IRStructType* irType, std::unordered_map<std::string, IRInstructionNode*> structValueSourceAllocationMap, IRGenerator* irGenerator, IRContext* irContext, IROperationType irOperationType) {
    if (node->isReferenced() || irOperationType == IR_COPY_GLOBAL_ASSIGNMENT_OP || irOperationType == IR_REF_GLOBAL_ASSIGNMENT_OP) {
        auto malloc = llvm::CallInst::Create(
                irContext->getIRModule()->getMallocFunction()->getFunctionType(),
                irContext->getIRModule()->getMallocFunction(),
                { irGenerator->generateIntConstant(irType->getSizeInBytes()) },
                ""
        );
        return IRInstructionNodeFactory::create(
                new llvm::BitCastInst(malloc, irType->getType()),
                irGenerator->generateIrPointerType(irType),
                { malloc },
                std::move(structValueSourceAllocationMap)
        );
    }
    return IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType), std::move(structValueSourceAllocationMap));
}