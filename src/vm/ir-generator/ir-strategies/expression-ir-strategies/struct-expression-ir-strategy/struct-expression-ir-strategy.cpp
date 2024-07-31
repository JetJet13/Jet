//
// Created by Johny Georges on 2024-06-21.
//

#include "struct-expression-ir-strategy.h"
#include "../../../../utils/address-space-generator/address-space-generator.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

IRStructExpressionNode* StructExpressionIRStrategy::generate(ASTStructExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    Logger::log("StructExpressionIRStrategy", node->getTypeSignature()->toString());
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature());
    auto structValues = std::vector<IRExpressionNode*>();
    for (auto keyValuePair : node->getKeyValuePairs()) {
        Logger::log("StructExpressionIRStrategy key value", keyValuePair->getKey()->getId(), keyValuePair->getValue()->getTypeSignature()->toString());
        auto irNode = irGenerator->generateFor(keyValuePair->getValue(), scope, irModule);
        structValues.push_back(irNode);
    }

    auto structAllocation = IRInstructionNodeFactory::create(irType);
    return new IRStructExpressionNode(node, structAllocation, irType, structValues);
}