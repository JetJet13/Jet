//
// Created by Johny Georges on 2024-06-26.
//

#include "identifier-expression-ir-strategy.h"

IRExpressionNode* IdentifierExpressionIRStrategy::generate(ASTIdentifierExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRLookupTable* scope) {
    return (IRExpressionNode*)scope->find(node->getIdentifierNode()->getId());
}