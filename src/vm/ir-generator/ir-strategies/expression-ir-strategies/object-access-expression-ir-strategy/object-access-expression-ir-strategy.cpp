//
// Created by Johny Georges on 2024-07-16.
//

#include "object-access-expression-ir-strategy.h"

IRObjectAccessExpressionNode* ObjectAccessExpressionIRStrategy::ObjectAccessExpressionIRStrategy::generate(ASTObjectAccessExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto sourceValue = irGenerator->generateFor(node->getSource(), scope, irModule);
    auto targetKey = node->getTarget()->getTarget()->getIdentifierNode()->getId();
    return new IRObjectAccessExpressionNode(node, sourceValue, targetKey, targetIndex, irGenerator->generateIntConstant(targetIndex));
}