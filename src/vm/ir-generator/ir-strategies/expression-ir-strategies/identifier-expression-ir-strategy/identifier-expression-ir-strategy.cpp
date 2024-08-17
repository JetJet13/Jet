//
// Created by Johny Georges on 2024-06-26.
//

#include "identifier-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-global-identifier-expression-node.h"

IRExpressionNode* IdentifierExpressionIRStrategy::generate(ASTIdentifierExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRLookupTable* scope, IRModuleNode* irModule, IROperationType irOperationType) {
    auto allocation = scope->find(node->getIdentifierNode()->getId());
    if (allocation) {
        return new IRIdentifierExpressionNode(node, allocation.value());
    }

    auto globalVariable = scope->findGlobalVariable(node->getIdentifierNode()->getId()).value();
    return new IRGlobalIdentifierExpressionNode(
            node,
            globalVariable
    );
}