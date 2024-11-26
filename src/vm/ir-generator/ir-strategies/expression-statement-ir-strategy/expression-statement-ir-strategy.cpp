//
// Created by Johny Georges on 2024-11-25.
//

#include "expression-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-expression-statement-node.h"

IRStatementNode* ExpressionStatementIRStrategy::generate(ASTExpressionStatementNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    return new IRExpressionStatementNode(node, irGenerator->generateFor(node->getExpression(), scope, irModule, IR_OPERAND_OP));
}