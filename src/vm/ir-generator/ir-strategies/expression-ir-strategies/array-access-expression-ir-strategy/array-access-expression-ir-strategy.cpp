//
// Created by Johny Georges on 2024-06-21.
//

#include "array-access-expression-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"

IRArrayAccessExpressionNode* ArrayAccessExpressionIRStrategy::ArrayAccessExpressionIRStrategy::generate(ASTArrayAccessExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    Logger::log("sourceValue type sig", node->getSource()->getTypeSignature()->toString());
    Logger::log("indexValue type sig", node->getIndex()->getIndex()->getTypeSignature()->toString());
    auto sourceValue = irGenerator->generateFor(node->getSource(), scope, irModule);
    auto indexValue = irGenerator->generateFor(node->getIndex()->getIndex(), scope, irModule);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature());
    return new IRArrayAccessExpressionNode(node, sourceValue, indexValue, irType);
}