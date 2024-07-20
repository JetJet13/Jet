//
// Created by Johny Georges on 2024-07-16.
//

#include "object-access-expression-ir-strategy.h"

IRObjectAccessExpressionNode* ObjectAccessExpressionIRStrategy::ObjectAccessExpressionIRStrategy::generate(ASTObjectAccessExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto sourceValue = irGenerator->generateFor(node->getSource()->getSource(), scope, irModule);
    auto sourceType = (IRStructType*)irGenerator->generateTypeFor(node->getSource()->getSource()->getTypeSignature());
    auto targetKey = node->getTarget()->getTarget()->getIdentifierNode()->getId();
    auto targetIndex = sourceType->getIndexForKey(targetKey);
    return new IRObjectAccessExpressionNode(node, sourceValue, sourceType, targetKey, targetIndex, irGenerator->generateIntConstant(targetIndex));
}