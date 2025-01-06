//
// Created by Johny Georges on 2025-01-06.
//

#ifndef JETLANG_VARIABLE_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
#define JETLANG_VARIABLE_ASSIGNMENT_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-declaration-node.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-variable-assignment-statement-node.h"

class VariableAssignmentStatementIRStrategy {
public:
    IRStatementNode* generate(ASTVariableAssignmentStatementNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule);
};

#endif //JETLANG_VARIABLE_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
