//
// Created by Johny Georges on 2025-02-17.
//

#ifndef JETLANG_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
#define JETLANG_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-array-access-assignment-statement-node.h"

class ArrayAccessAssignmentStatementIRStrategy {
public:
    IRStatementNode* generate(ASTArrayAccessAssignmentStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
