//
// Created by Johny Georges on 2024-06-21.
//

#include "array-access-expression-ir-strategy.h"

IRArrayAccessExpressionNode* ArrayAccessExpressionIRStrategy::ArrayAccessExpressionIRStrategy::generate(ASTArrayAccessExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    auto sourceValue = irGenerator->generateFor(node->getSource(), scope);
    auto indexValue = irGenerator->generateFor(node->getIndex()->getIndex(), scope);
    return new IRArrayAccessExpressionNode(node, sourceValue, indexValue);
}