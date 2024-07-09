//
// Created by Johny Georges on 2024-06-26.
//

#include "identifier-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"

IRExpressionNode* IdentifierExpressionIRStrategy::generate(ASTIdentifierExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRLookupTable* scope, IRModuleNode* irModule) {
    return new IRIdentifierExpressionNode(node, scope->find(node->getIdentifierNode()->getId()));
}