//
// Created by Johny Georges on 2025-08-30.
//

#ifndef JETLANG_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
#define JETLANG_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-object-access-assignment-statement-node.h"

class ObjectAccessAssignmentStatementIRStrategy {
public:
    IRStatementNode* generate(ASTObjectAccessAssignmentStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
