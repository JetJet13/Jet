//
// Created by Johny Georges on 2025-01-06.
//

#include "variable-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-variable-assignment-statement-node.h"

IRStatementNode* VariableAssignmentStatementIRStrategy::generate(ASTVariableAssignmentStatementNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    return new IRVariableAssignmentStatementNode(node, irGenerator->generateFor(node->getExpression(), scope, irModule, IR_OPERAND_OP));
}